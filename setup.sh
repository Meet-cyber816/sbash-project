#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Print with color
print_status() {
    echo -e "${BLUE}[*]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[+]${NC} $1"
}

print_error() {
    echo -e "${RED}[-]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[!]${NC} $1"
}

# Function to check command status
check_status() {
    if [ $? -eq 0 ]; then
        print_success "$1"
    else
        print_error "$2"
        exit 1
    fi
}

# Function to detect package manager
get_package_manager() {
    if command -v apt-get &> /dev/null; then
        echo "apt-get"
    elif command -v yum &> /dev/null; then
        echo "yum"
    elif command -v dnf &> /dev/null; then
        echo "dnf"
    elif command -v pacman &> /dev/null; then
        echo "pacman"
    else
        print_error "No supported package manager found!"
        exit 1
    fi
}

# Detect package manager
PACKAGE_MANAGER=$(get_package_manager)

print_status "Starting sbash installation..."

# Check if gcc is installed
if ! command -v gcc &> /dev/null; then
    print_status "GCC not found. Installing gcc..."
    sudo $PACKAGE_MANAGER install -y gcc
    check_status "GCC installed successfully" "Failed to install gcc"
else
    print_status "GCC already installed"
fi

# Get actual username
USER_HOME=$(eval echo ~$(logname))
SBASH_DIR="$USER_HOME/.sbash"
LOCAL_BIN="/usr/local/bin"

# Ensure .sbash directory exists
print_status "Creating .sbash directory..."
mkdir -p "$SBASH_DIR"
check_status "Created .sbash directory" "Failed to create .sbash directory"

# Move all files into .sbash
print_status "Copying files to .sbash directory..."
cp -r "$(pwd)"/* "$SBASH_DIR"
check_status "Files copied successfully" "Failed to copy files"
cp .uninstall.sh "$SBASH_DIR/.uninstall.sh"

# Change directory to .sbash
cd "$SBASH_DIR"

# Check for required files
print_status "Checking required files..."
if [ ! -f sbash ]; then
    print_error "sbash file not found!"
    exit 1
fi

# If black_commands.txt exists, run sbash_input
if [ -f black_commands.txt ]; then
    print_status "Configuring restricted commands..."
    ./sbash_input
    check_status "Restricted commands configured" "Failed to configure restricted commands"
fi

# Move sbash 
print_status "Installing sbash to system..."
sudo mv sbash "$LOCAL_BIN/"
check_status "sbash installed to $LOCAL_BIN" "Failed to install sbash"

# Set execute permissions
sudo chmod +x "$LOCAL_BIN/sbash"
check_status "Set execute permissions" "Failed to set execute permissions"

# Creating man file for use of safer man
sudo touch "$LOCAL_BIN/man"
sudo bash -c "echo '#!/bin/bash
LESSSECURE=1 LESS=\"-is\" /usr/bin/man \"\$@\"' > \"$LOCAL_BIN/man\""
sudo chmod +x "$LOCAL_BIN/man"

# Add sbash to /etc/shells
print_status "Configuring system shells..."
if ! grep -q "$LOCAL_BIN/sbash" /etc/shells; then
    echo "$LOCAL_BIN/sbash" | sudo tee -a /etc/shells
    check_status "Added sbash to /etc/shells" "Failed to add sbash to /etc/shells"
fi

# Add exec command to .bashrc
print_status "Configuring .bashrc..."
echo -e "\n# Sbash Configuration" >> "$USER_HOME/.bashrc"
echo "exec /usr/local/bin/sbash" >> "$USER_HOME/.bashrc"
check_status ".bashrc configured" "Failed to configure .bashrc"

# Create uninstall.c and compile it
print_status "Creating uninstaller..."
touch uninstall.c
echo '#include <stdlib.h>
int main() {
    system("sudo chmod +x .uninstall.sh && sudo ./.uninstall.sh");
    return 0;
}' > uninstall.c

# Compile uninstaller
print_status "Compiling uninstaller..."
gcc uninstall.c -o uninstall
check_status "Uninstaller compiled" "Failed to compile uninstaller"
chmod +x uninstall

# Remove source file
print_status "Cleaning up..."
rm -f uninstall.c

sudo chattr +i $USER_HOME/.bashrc
sudo chattr +i $USER_HOME/.bash_logout
sudo chattr +i $USER_HOME/.profile
sudo chattr +i $USER_HOME/.bash_profile

print_success "Sbash installation completed successfully!"
print_status "To uninstall, go to ~/.sbash and run './uninstall' command from Terminal."
print_status "Please restart your terminal to run sbash."
exit 0


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

print_status "Starting Secure Terminal (sbash) uninstallation..."

# Get actual username
USER_HOME=$(eval echo ~$(logname))
SBASH_DIR="$USER_HOME/.sbash"
LOCAL_BIN="/usr/local/bin"

sudo chattr -i $USER_HOME/.bashrc

# Remove sbash from /etc/shells
print_status "Removing sbash from system shells..."
if grep -q "$LOCAL_BIN/sbash" /etc/shells; then
    sudo sed -i "\|$LOCAL_BIN/sbash|d" /etc/shells
    check_status "Removed sbash from /etc/shells" "Failed to remove sbash from /etc/shells"
fi

# Remove sbash executable
print_status "Removing sbash executable..."
if [ -f "$LOCAL_BIN/sbash" ]; then
    sudo rm "$LOCAL_BIN/sbash"
    check_status "Removed sbash executable" "Failed to remove sbash executable"
fi


# Remove sbash configuration from .bashrc
print_status "Removing sbash configuration from .bashrc..."
if grep -q "# Secure Terminal Configuration" "$USER_HOME/.bashrc"; then
    sed -i '/# Secure Terminal Configuration/,/exec \/usr\/local\/bin\/sbash/d' "$USER_HOME/.bashrc"
    check_status "Removed sbash configuration from .bashrc" "Failed to remove sbash configuration from .bashrc"
fi

# Remove .sbash directory
print_status "Removing .sbash directory..."
if [ -d "$SBASH_DIR" ]; then
    rm -rf "$SBASH_DIR"
    check_status "Removed .sbash directory" "Failed to remove .sbash directory"
fi

print_success "Secure Terminal (sbash) uninstallation completed successfully!"
print_status "Please restart your terminal."
exit 0 

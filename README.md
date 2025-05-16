# Sbash - Secure Bash Shell (Standard Edition)

Sbash (Secure Bash Shell) is a system-level security software designed as a more secure alternative to the standard Bash shell for organizations, enterprises, and educational institutions seeking to secure their systems.

**This repository contains the source code for Sbash Standard Edition, which is available as open source software.**

## Overview

Sbash enhances Linux security by integrating directly with the Bash shell, providing real-time protection against command-line threats while maintaining full compatibility with all major distributions and desktop environments.

### Key Features

- **Advanced Protection**: Employs proper input validation and command parsing to detect and neutralize threats
- **Command Restriction**: Blocks potentially dangerous commands that could compromise system security
- **Special Character Filtering**: Prevents the use of special characters that could be used for malicious purposes
- **Low Resource Usage**: Minimal impact on system performance
- **Easy Integration**: Works with existing Linux systems and security infrastructure
- **Open Source**: Free to use, modify, and distribute under open source terms

### Protection Against

- Unauthorized sudo access
- Unauthorized command execution
- Unauthorized file access
- System damage via dangerous commands

## Installation

### Prerequisites

You need to install the readline development library:

#### For Fedora/RHEL
```
sudo dnf install readline-devel
```

#### For Ubuntu/Debian
```
sudo apt install libreadline-dev
```

### Compile Sbash

```
gcc sbash.c -o sbash -lreadline
gcc sbash_input.c -o sbash_input
```

### Setup Sbash on the System

```
chmod +x setup.sh && sudo ./setup.sh
```

After installation, close and reopen your terminal to start using Sbash.

## Uninstalling Sbash

If you need to uninstall Sbash, run:

```
cd ~/.sbash 
./uninstall
```

## Editions

### Standard Edition (This Repository)

This repository contains the open source Standard Edition of Sbash, which is perfect for individual users or home environments. The Standard Edition provides comprehensive security with a user-friendly interface.

- Single-user operation
- Complete command protection
- Easy to install and configure
- Free and open source

### Admin-Controlled Edition

Designed for organizations, educational institutions, and controlled environments where security policies need to be enforced.

- Controller/controlled user model
- Administrator-defined security policies
- Perfect for labs and shared systems

## How Sbash Works

Sbash works by:

1. Intercepting user commands before they're executed
2. Validating commands against a blacklist of restricted commands
3. Checking for dangerous special characters and flags
4. Preventing access to sensitive system directories
5. Providing a secure environment for normal daily operations

## Project Creator

Meet Panchal  
Contact: tedomanoffsec@gmail.com  
LinkedIn: https://www.linkedin.com/in/meet-panchal-434709316/

## Contributing

As an open source project, contributions to Sbash are welcome! Feel free to fork this repository, make improvements, and submit pull requests.

## License

This project is released as open source software. You are free to use, modify, and distribute this software according to the terms of the license.

---

For more information, visit [the website](https://sbash-security-software.onrender.com/)
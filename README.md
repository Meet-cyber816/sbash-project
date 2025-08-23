<h1 align="center">Sbash - Secure Bash Shell</h1>
<div align="center">

<img src="https://img.shields.io/badge/Security-Enhanced-brightgreen?style=for-the-badge" alt="Security Enhanced">
<img src="https://img.shields.io/badge/Shell-Bash-blue?style=for-the-badge" alt="Bash Shell">
<img src="https://img.shields.io/badge/License-Open%20Source-yellow?style=for-the-badge" alt="Open Source">

**A system-level security software designed as a more secure alternative to the standard Bash shell**

**For organizations, enterprises, and educational institutions seeking to secure their systems**

---

### 🎥 Project Overview Video

**[📺 Watch on YouTube](https://youtu.be/DgHcm1yww8E?si=itSsFbXp1MBdWb5U*)**

https://youtu.be/DgHcm1yww8E?si=itSsFbXp1MBdWb5U

---

</div>

## 📋 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-Features)
- [Protection Against](#%EF%B8%8F-protection-against)
- [Installation](#-installation)
- [Uninstalling Sbash](#%EF%B8%8F-uninstalling-sbash)
- [Editions](#-editions)
- [How Sbash Works](#%EF%B8%8F-how-sbash-works)
- [Project Creator](#-project-creator)
- [Contributing](#-contributing)
- [License](#-license)

## 🔍 Overview

Sbash enhances Linux security by integrating directly with the Bash shell, providing real-time protection against command-line threats while maintaining full compatibility with all major distributions and desktop environments.

**This repository contains the source code for Sbash Standard Edition, which is available as open source software.**

## ✨ Key Features

- **🛡️ Advanced Protection**: Employs proper input validation and command parsing to detect and neutralize threats
- **🚫 Command Restriction**: Blocks potentially dangerous commands that could compromise system security
- **🔤 Special Character Filtering**: Prevents the use of special characters that could be used for malicious purposes
- **⚡ Low Resource Usage**: Minimal impact on system performance
- **🔧 Easy Integration**: Works with existing Linux systems and security infrastructure
- **📖 Open Source**: Free to use, modify, and distribute under open source terms

## 🛡️ Protection Against

- Unauthorized sudo access
- Unauthorized command execution
- Unauthorized file access
- System damage via dangerous commands

## 🚀 Installation

### Prerequisites

You need to install the readline development library:

#### For Fedora/RHEL
```bash
sudo dnf install readline-devel
```

#### For Ubuntu/Debian
```bash
sudo apt install libreadline-dev
```

### Compile Sbash

```bash
gcc sbash.c -o sbash -lreadline
gcc sbash_input.c -o sbash_input
```

### Setup Sbash on the System

```bash
chmod +x setup.sh && sudo ./setup.sh
```

> **Note:** After installation, close and reopen your terminal to start using Sbash.

## 🗑️ Uninstalling Sbash

If you need to uninstall Sbash, run:

```bash
cd ~/.sbash 
./uninstall
```

## 📦 Editions

### Standard Edition (This Repository)

This repository contains the open source Standard Edition of Sbash, which is perfect for individual users or home environments. The Standard Edition provides comprehensive security with a user-friendly interface.

- ✅ Single-user operation
- ✅ Complete command protection
- ✅ Easy to install and configure
- ✅ Free and open source

### Admin-Controlled Edition

Designed for organizations, educational institutions, and controlled environments where security policies need to be enforced.

- 👥 Controller/controlled user model
- 📋 Administrator-defined security policies
- 🏫 Perfect for labs and shared systems

## ⚙️ How Sbash Works

Sbash works by:

1. **🔍 Intercepting** user commands before they're executed
2. **✅ Validating** commands against a blacklist of restricted commands
3. **🔍 Checking** for dangerous special characters and flags
4. **🚫 Preventing** access to sensitive system directories
5. **🛡️ Providing** a secure environment for normal daily operations

## 👨‍💻 Project Creator

**Meet Panchal**  
📧 Contact: tedomanoffsec@gmail.com  
🔗 LinkedIn: https://www.linkedin.com/in/meeet-panchal

## 🤝 Contributing

As an open source project, contributions to Sbash are welcome! Feel free to fork this repository, make improvements, and submit pull requests.

## 📄 License

This project is released as open source software. You are free to use, modify, and distribute this software according to the terms of the license.

---

<div align="center">

**⭐ Star this repository if you find it useful!**

</div>

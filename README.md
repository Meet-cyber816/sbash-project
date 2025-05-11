# Download readline library 
## For Fedora
```
sudo dnf install readline-devel
```
## For Ubuntu
```
sudo apt install libreadline-dev
```
## Now compile sbash and sbash_input.c using following commands
```
gcc sbash.c -o sbash -lreadline
gcc sbash_input.c -o sbash_input
```
# Setup sbash on the system
### Run the following command
```
chmod +x setup.sh && sudo ./setup.sh
```
### Now open close the Terminal and reopen it now you have sbash properly setted up
# Uninstall sbash
### Run following command
```
cd ~/.sbash && ./uninstall
```
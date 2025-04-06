# Download readline library 
## For Fedora
```
sudo dnf install readline-devel
```
## For Ubuntu
```
sudo apt install libreadline-dev
```
# Now compile sbash and sbash_input.c using following commands
```
gcc sbash.c -o sbash -lreadline
gcc sbash_input.c -o sbash_input
```

# Toast App

This app is made with SDL2, so it's cross-platform, but you may have to install SDL2 libs to compile it.

### Compiling
```bash
$ make build
```
### Add to path
```bash
$ echo "export PATH=$PATH:/path/to/toast" >> ~/.bashrc
$ source ~/.bashrc
```
### Run
```bash
$ toast [params] :
    -t      text to display
    -p      place to display {bottomright, bottomleft, topright, topleft} (default bottomright)
    -d      lifetime (default 5)
    -w      custom width (default fit well with text)
    -h      custom height (default fit well with text)
    --help  this
```

_**Click on window to close it**_

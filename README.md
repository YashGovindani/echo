# echo
Echo is a audio streaming server used to stream audio from device.

```Note: Currently Achieving for mac```

#### Why we need Blackhole Virtual Device ?
We want to capture system audio

# server

### compile AudioServer.java
```
javac  AudioServer.java
```

### run AudioServer.java
```
java  AudioServer
```

### install blackhole 2ch

```
sudo installer -pkg ./BlackHole.pkg -target /
```

### compile setBlackHole.c
```
gcc -o setBlackHole setBlackHole.c -framework CoreAudio -framework CoreFoundation
```

# client

### compile AudioStreamingClient.java
```
javac AudioStreamingClient.java
```

### running AudioStreamingClient
```
java AudioStreamingClient
```
set sampling_frequency=11025
vlc -vv %1 --sout "#transcode{acodec=mp3, ab=128, channels=2, samplerate=44100}:std{access=file, mux=raw, dst="temp.mp3"}" vlc://quit
convert_mp3 temp.mp3
del temp.mp3 /Q
out.wav
@pause
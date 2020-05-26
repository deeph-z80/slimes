ffmpeg -y -i %1 temp.wav
set sampling_frequency=11025
sox -V -D temp.wav -r %sampling_frequency% -e unsigned-integer -b 8 -c 1 out.wav rate %sampling_frequency%
del temp.wav /Q
out.wav
@pause
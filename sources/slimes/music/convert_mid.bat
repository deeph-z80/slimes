set sampling_frequency=11025
timidity %1 -Ow -o temp.wav
sox -V -D temp.wav -r %sampling_frequency% -e unsigned-integer -b 8 -c 1 out.wav rate %sampling_frequency%
del temp.wav /q
out.wav
@pause
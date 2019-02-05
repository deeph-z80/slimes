set sampling_frequency=11025
REM ffmpeg -y -i %1 -acodec pcm_u8 -ar %sampling_frequency% -ac 1 out.wav
sox -V -D %1 -r %sampling_frequency% -e unsigned-integer -b 8 -c 1 out.wav rate %sampling_frequency%
out.wav
@pause
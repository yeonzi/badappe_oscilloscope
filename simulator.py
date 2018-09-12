import wave
import numpy as np

print "Input File Name"
#filename = raw_input()
filename = "out"
filename += ".wav"

try:
    fp = wave.open(filename,"rb")
except Exception as err:
        print(err)
        exit(0)

param = fp.getparams()
nchannels,sampwidth,framerate,nframes = param[:4]
print "WAV param"

print "channels = %d, sampwidth = %d, framerate = %d, nframes = %d, compname = %s" % ( nchannels,sampwidth,framerate,nframes,param[4] )

fp_data = fp.readframes(nframes)

fp.close()

wav_data = np.fromstring(fp_data,dtype=np.short)
print wav_data
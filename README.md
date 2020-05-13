# Dense Optical Flow

Dense optical flow matrix using OpenCV's Gunnar Farneback’s algorithm.

# Compilation

```
mkdir build && pushd !!
cmake ..
make
popd
```

# Usage

```
./doflow VIDEO_FILE.mp4
```

# Output sample

![](running.gif)

# Tools
```
ffmpeg -y -i KTH-Final-0TbZXdhqvA.mp4 -ss 50 -vf eq=brightness=-0.3:contrast=-0.5:saturation=0.5,scale=800:-1 -an KTH-Final-0TbZXdhqvA-640.mp4
ffmpeg -y -i 2020-05-12_08-14-26.mp4 -filter:v "crop=760:420:0:0" out.mp4; mplayer out.mp4
```

# Credits

* Video cut from Richard Ristic, https://www.youtube.com/watch?v=-0TbZXdhqvA; the video has been processed to decrease brightness in order to make the rows more visible. Will be removed if the author asks for.
* See https://stackoverflow.com/questions/43482959/simple-dense-optical-flow-program-calcopticalflowfarneback-opencv-3-2-cpp
* See also https://github.com/gti-upm/FFME

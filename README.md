# brain-dump
This brain-dump contains codes that I have been working on or worked on during my professional life. I have been coding for almost 
15 years but I have never properly documented my projects. This brain-dump will be a good reference for anybody who wants to start
coding seriously (I guess).

# brain-dump 25/8/2017
Updated two codes for producing simple unstructured and structured raw binary data in VTK XML format. The format is used in
Paraview software. Raw binary data is known to be machine specific, but generally, little-endian type is common for Windows
and Linux box, so its quite safe to use. The main benefit of raw binary data is size. Data file saved in raw binary is roughly 
1/3 the size of equivalent ASCII format data file. Plus, read/write speed is an order of magnitude faster (maybe two order, I 
could not remember the specific, but hey, its fast) compared to ASCII format files.

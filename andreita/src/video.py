
#from __future__ import print_function
import cv2.cv as cv
import time
import numpy as np
import cv2
from matplotlib import pyplot as plt

ply_header = '''ply
format ascii 1.0
element vertex %(vert_num)d
property float x
property float y
property float z
property uchar red
property uchar green
property uchar blue
end_header
'''


def write_ply(fn, verts, colors):
    verts = verts.reshape(-1, 3)
    colors = colors.reshape(-1, 3)
    verts = np.hstack([verts, colors])
    with open(fn, 'wb') as f:
        f.write((ply_header % dict(vert_num=len(verts))).encode('utf-8'))
        np.savetxt(f, verts, fmt='%f %f %f %d %d %d ')

# disparity settings
window_size = 5
min_disp = 32
num_disp = 112-min_disp
stereo = cv2.StereoSGBM(
    minDisparity = min_disp,
    numDisparities = num_disp,
    SADWindowSize = window_size,
    uniquenessRatio = 10,
    speckleWindowSize = 100,
    speckleRange = 32,
    disp12MaxDiff = 1,
    P1 = 8*3*window_size**2,
    P2 = 32*3*window_size**2,
    fullDP = False
)



#counter = 450
#capture = cv.CaptureFromCAM(0)


#while counter < 650:

    # increment counter
#    counter += 1

    # only process every third image (so as to speed up video)
#    if counter % 3 != 0: continue

    # load stereo image
#    filename = str(counter).zfill(4)



    #image_right = cv2.imread('ambush_5_right.jpg',1)
    #image_left = cv2.imread('ambush_5_left.jpg',1)
#    cv.ShowImage("camera", img)




# compute disparity
    #disparity = stereo.compute(image_left, image_right).astype(np.float32) / 16.0
    #disparity = (disparity-min_disp)/num_disp
    #cv2.imshow('left eye', image_left)
    #cv2.imshow('right eye', image_right)
    #cv2.imshow('disparity', disparity)




    #print('generating 3d point cloud...',)
    #h, w = image_left.shape[:2]
    #f = 0.8*w                          # guess for focal length
    #Q = np.float32([[1, 0, 0, -0.5*w],
    #                [0,-1, 0,  0.5*h], # turn points 180 deg around x-axis,
    #                [0, 0, 0,     -f], # so that y-axis looks up
    #                [0, 0, 1,      0]])
    #points = cv2.reprojectImageTo3D(disparity, Q)
    #colors = cv2.cvtColor(image_left, cv2.COLOR_BGR2RGB)
    #colores = cv2.cvtColor(disparity, cv2.COLOR_BGR2RGB)
    #mask = disparity > disparity.min()
    #out_points = points[mask]
    #out_colors = colors[mask]
    #out_fn = 'out.ply'
    #write_ply('out.ply', out_points, out_colors)
    #print('%s saved' % 'out.ply')

    #cv2.imshow('colores', colores)



img1 = cv2.imread('ambush_5_right.jpg',0)  #queryimage # left image
img2 = cv2.imread('ambush_5_left.jpg',0) #trainimage # right image

P2 = array([[ 0.878, -0.01 ,  0.479, -1.995],
            [ 0.01 ,  1.   ,  0.002, -0.226],
            [-0.479,  0.002,  0.878,  0.615],
            [ 0.   ,  0.   ,  0.   ,  1.   ]])
# Homogeneous arrays
a3xN = array([[ 0.091,  0.167,  0.231,  0.083,  0.154],
              [ 0.364,  0.333,  0.308,  0.333,  0.308],
              [ 1.   ,  1.   ,  1.   ,  1.   ,  1.   ]])
b3xN = array([[ 0.42 ,  0.537,  0.645,  0.431,  0.538],
              [ 0.389,  0.375,  0.362,  0.357,  0.345],
              [ 1.   ,  1.   ,  1.   ,  1.   ,  1.   ]])

cv.WaitKey(10)
cv.DestroyAllWindows()

'1.发布照片'

- CMakeL.ists

#!/usr/bin/env python
import cv2
import rospy
import os
import numpy as np
import sys
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

DATA_PATH='/home/kim/kitti/2011_09_26_drive_0005_sync/2011_09_26/2011_09_26_drive_0005_sync/'

if __name__ == '__main__':
frame = 0
rospy.init_node('kitti_node',anonymous=True)
cam_pub = rospy.Publisher('kitti_cam',Image,queue_size=10)
bridge = CvBridge()
rate = rospy.Rate(10)

while not rospy.is_shutdown():
img = cv2.imread(os.path.join(DATA_PATH,'image_02/data/%010d.png'%frame))#读取10个0名称的照片
cam_pub.publish(bridge.cv2_to_imgmsg(img,'bgr8'))
rospy.loginfo('camera image published')
rate.sleep()
frame += 1
frame %= 154

- package.xml
    <buildtool_depend>catkin</buildtool_depend>
    <build_depend>roscpp</build_depend>
    <build_depend>rospy</build_depend>
    <build_depend>std_msgs</build_depend>
    <build_depend>sensor_msgs</build_depend>
    <build_depend>cv_bridge</build_depend>
    <build_depend>opencv2</build_depend>
    <build_depend>message_generation</build_depend>
    <build_depend>message_runtime</build_depend>
- <build_export_depend>roscpp</build_export_depend>
    <build_export_depend>rospy</build_export_depend>
    <build_export_depend>std_msgs</build_export_depend>
    <build_export_depend>sensor_msgs</build_export_depend>
    <build_export_depend>cv_bridge</build_export_depend>
    <build_export_depend>opencv2</build_export_depend>
    <build_export_depend>message_generation</build_export_depend>
    <build_export_depend>message_runtime</build_export_depend>
- <exec_depend>roscpp</exec_depend>
    <exec_depend>rospy</exec_depend>
    <exec_depend>std_msgs</exec_depend>
    <exec_depend>sensor_msgs</exec_depend>
    <exec_depend>cv_bridge</exec_depend>
    <exec_depend>opencv2</exec_depend>
    <exec_depend>message_runtime</exec_depend>
    <exec_depend>message_generation</exec_depend>
- .编辑配置文件：CMakeLists

find_package(catkin REQUIRED COMPONENTS
roscpp
rospy
std_msgs
sensor_msgs
cv_bridge
)

add_message_files(
FILES
Image.msg
)

catkin_package(

# INCLUDE_DIRS include

# LIBRARIES kitti_tutorial

CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs cv_bridge

# DEPENDS system_lib

)

catkin_install_python(PROGRAMS
scripts/pub.py
scripts/sub.py
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

2.publish_utils

python
#!/usr/bin/env python
import rospy
from std_msgs.msg import Header
from visualization_msgs.msg import Marker
from sensor_msgs.msg import Image, PointCloud2, Imu, NavSatFix
from geometry_msgs.msg import Point
import sensor_msgs.point_cloud2 as pcl2
from cv_bridge import CvBridge
import tf
import numpy as np
FRAME_ID = 'map'

def publish_camera(cam_pub, bridge, image):
cam_pub.publish(bridge.cv2_to_imgmsg(image,"bgr8"))

def publish_point_cloud(pcl_pub,point_cloud):
header = Header()
header.stamp = rospy.Time.now()
header.frame_id = FRAME_ID
pcl_pub.publish(pcl2.create_cloud_xyz32(header, point_cloud[:,:3]))

def publish_ego_car(ego_car_pub):
# publish left and right 45 degree FOV lines and ego car model mesh
marker = Marker()
marker.header.frame_id = FRAME_ID
marker.header.stamp = rospy.Time.now()
marker.id = 0
marker.action = Marker.ADD
marker.lifetime = rospy.Duration()
marker.type = Marker.LINE_STRIP
# line
marker.color.r = 0.0
marker.color.g = 1.0
marker.color.b = 0.0
marker.color.a = 1.0
marker.scale.x = 0.2 # line width

marker.points = []

# check the kitti axis model 
marker.points.append(Point(5,-5,0)) # left up
marker.points.append(Point(0,0,0)) # center
marker.points.append(Point(5, 5,0)) # right up

ego_car_pub.publish(marker)


python
def publish_car_model(model_pub):
mesh_marker = Marker()
mesh_marker.header.frame_id = FRAME_ID
mesh_marker.header.stamp = rospy.Time.now()

mesh_marker.id = -1
mesh_marker.lifetime = rospy.Duration()
mesh_marker.type = Marker.MESH_RESOURCE
mesh_marker.mesh_resource = "package://demo_01/Audi R8/Models/AudiR8.dae"

mesh_marker.pose.position.x = 0.0
mesh_marker.pose.position.y = 0.0
mesh_marker.pose.position.z = -1.73

q = tf.transformations.quaternion_from_euler(np.pi/2,0,np.pi)
mesh_marker.pose.orientation.x = q[0]
mesh_marker.pose.orientation.y = q[1]
mesh_marker.pose.orientation.z = q[2]
mesh_marker.pose.orientation.w = q[3]

mesh_marker.color.r = 1.0
mesh_marker.color.g = 1.0
mesh_marker.color.b = 1.0
mesh_marker.color.a = 1.0

mesh_marker.scale.x = 0.9
mesh_marker.scale.y = 0.9
mesh_marker.scale.z = 0.9

model_pub.publish(mesh_marker)


def publish_imu(imu_pub, imu_data, log=False):
"""
Publish IMU data
http://docs.ros.org/melodic/api/sensor_msgs/html/msg/Imu.html
"""
imu = Imu()
imu.header.frame_id = FRAME_ID
imu.header.stamp = rospy.Time.now()
q = tf.transformations.quaternion_from_euler(float(imu_data.roll), float(imu_data.pitch),
float(imu_data.yaw)) # prevent the data from being overwritten
imu.orientation.x = q[0]
imu.orientation.y = q[1]
imu.orientation.z = q[2]
imu.orientation.w = q[3]
imu.linear_acceleration.x = imu_data.af
imu.linear_acceleration.y = imu_data.al
imu.linear_acceleration.z = imu_data.au
imu.angular_velocity.x = imu_data.wf
imu.angular_velocity.y = imu_data.wl
imu.angular_velocity.z = imu_data.wu

imu_pub.publish(imu)
if log:
    rospy.loginfo("imu msg published")


def publish_gps(gps_pub, gps_data, log=False):
"""
Publish GPS data
"""
gps = NavSatFix()
gps.header.frame_id = FRAME_ID
gps.header.stamp = rospy.Time.now()
gps.latitude = gps_data.lat
gps.longitude = gps_data.lon
gps.altitude = gps_data.alt


gps_pub.publish(gps)
if log:
    rospy.loginfo("gps msg published")


3.draw_3d_plot

'1.kitti dataset exploration'

KITTI Dataset Exploration

import numpy as np
import pykitti

# Change this to the directory where you store KITTI data

basedir = 'data'

def load_dataset(date, drive, calibrated=False, frame_range=None):
"""
Loads the dataset with date and drive.


Parameters
----------
date        : Dataset creation date.
drive       : Dataset drive.
calibrated  : Flag indicating if we need to parse calibration data. Defaults to False.
frame_range : Range of frames. Defaults to None.

Returns
-------
Loaded dataset of type raw.
"""
dataset = pykitti.raw(basedir, date, drive)

# Load the data
if calibrated:
 dataset.load_calib()  # Calibration data are accessible as named tuples

np.set_printoptions(precision=4, suppress=True)
print('\nDrive: ' + str(dataset.drive))
print('\nFrame range: ' + str(dataset.frames))

if calibrated:
 print('\nIMU-to-Velodyne transformation:\n' + str(dataset.calib.T_velo_imu))
 print('\nGray stereo pair baseline [m]: ' + str(dataset.calib.b_gray))
 print('\nRGB stereo pair baseline [m]: ' + str(dataset.calib.b_rgb))

return dataset 


from source import parseTrackletXML as xmlParser

def load_tracklets_for_frames(n_frames, xml_path):
"""
Loads dataset labels also referred to as tracklets, saving them individually for each frame.


Parameters
----------
n_frames    : Number of frames in the dataset.
xml_path    : Path to the tracklets XML.

Returns
-------
Tuple of dictionaries with integer keys corresponding to absolute frame numbers and arrays as values. First array
contains coordinates of bounding box vertices for each object in the frame, and the second array contains objects
types as strings.
"""
tracklets = xmlParser.parseXML(xml_path)

frame_tracklets = {}
frame_tracklets_types = {}
for i in range(n_frames):
    frame_tracklets[i] = []
    frame_tracklets_types[i] = []

# loop over tracklets
for i, tracklet in enumerate(tracklets):
    # this part is inspired by kitti object development kit matlab code: computeBox3D
    h, w, l = tracklet.size
    # in velodyne coordinates around zero point and without orientation yet
    trackletBox = np.array([
        [-l / 2, -l / 2, l / 2, l / 2, -l / 2, -l / 2, l / 2, l / 2],
        [w / 2, -w / 2, -w / 2, w / 2, w / 2, -w / 2, -w / 2, w / 2],
        [0.0, 0.0, 0.0, 0.0, h, h, h, h]
    ])
    # loop over all data in tracklet
    for translation, rotation, state, occlusion, truncation, amtOcclusion, amtBorders, absoluteFrameNumber in tracklet:
        # determine if object is in the image; otherwise continue
        if truncation not in (xmlParser.TRUNC_IN_IMAGE, xmlParser.TRUNC_TRUNCATED):
            continue
        # re-create 3D bounding box in velodyne coordinate system
        yaw = rotation[2]  # other rotations are supposedly 0
        assert np.abs(rotation[:2]).sum() == 0, 'object rotations other than yaw given!'
        rotMat = np.array([
            [np.cos(yaw), -np.sin(yaw), 0.0],
            [np.sin(yaw), np.cos(yaw), 0.0],
            [0.0, 0.0, 1.0]
        ])
        cornerPosInVelo = np.dot(rotMat, trackletBox) + np.tile(translation, (8, 1)).T
        frame_tracklets[absoluteFrameNumber] = frame_tracklets[absoluteFrameNumber] + [cornerPosInVelo]
        frame_tracklets_types[absoluteFrameNumber] = frame_tracklets_types[absoluteFrameNumber] + [
            tracklet.objectType]

return (frame_tracklets, frame_tracklets_types) 


Load the dataset downloaded from KITTI website.

2011_09_26_drive_0001 (0.4 GB)


Length: 114 frames (00:11 minutes)
Image resolution: 1392 x 512 pixels
Labels: 12 Cars, 0 Vans, 0 Trucks, 0 Pedestrians, 0 Sitters, 2 Cyclists, 1 Trams, 0 Misc 


date = '2011_09_26'
drive = '0001'
dataset = load_dataset(date, drive)
tracklet_rects, tracklet_types = load_tracklets_for_frames(len(list(dataset.velo)), 'data/{}/{}drive{}_sync/tracklet_labels.xml'.format(date, date, drive))

Looking at the points distributions, we could catch something meaningful if we limit X, Y and Z axis to some magic numbers.

Additionally we will only visualise 20% of the point cloud, as each frame contains ~120K points.

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

colors = {
'Car': 'b',
'Tram': 'r',
'Cyclist': 'g',
'Van': 'c',
'Truck': 'm',
'Pedestrian': 'y',
'Sitter': 'k'
}
axes_limits = [
[-20, 80], # X axis range
[-20, 20], # Y axis range
[-3, 10] # Z axis range
]
axes_str = ['X', 'Y', 'Z']

def draw_box(pyplot_axis, vertices, axes=[0, 1, 2], color='black'):
"""
Draws a bounding 3D box in a pyplot axis.


Parameters
----------
pyplot_axis : Pyplot axis to draw in.
vertices    : Array 8 box vertices containing x, y, z coordinates.
axes        : Axes to use. Defaults to [0, 1, 2], e.g. x, y and z axes.
color       : Drawing color. Defaults to black.
"""
vertices = vertices[axes, :]
connections = [
    [0, 1], [1, 2], [2, 3], [3, 0],  # Lower plane parallel to Z=0 plane
    [4, 5], [5, 6], [6, 7], [7, 4],  # Upper plane parallel to Z=0 plane
    [0, 4], [1, 5], [2, 6], [3, 7]  # Connections between upper and lower planes
]
for connection in connections:
    pyplot_axis.plot(*vertices[:, connection], c=color, lw=0.5) 


def display_frame_statistics(dataset, tracklet_rects, tracklet_types, frame, points=0.2):
"""
Displays statistics for a single frame. Draws camera data, 3D plot of the lidar point cloud data and point cloud
projections to various planes.


Parameters
----------
dataset         : raw dataset.
tracklet_rects  : Dictionary with tracklet bounding boxes coordinates.
tracklet_types  : Dictionary with tracklet types.
frame           : Absolute number of the frame.
points          : Fraction of lidar points to use. Defaults to 0.2, e.g. 20%.
"""
dataset_gray = list(dataset.gray)
dataset_rgb = list(dataset.rgb)
dataset_velo = list(dataset.velo)

print('Frame timestamp: ' + str(dataset.timestamps[frame]))
# Draw camera data
f, ax = plt.subplots(2, 2, figsize=(15, 5))
ax[0, 0].imshow(dataset_gray[frame][0], cmap='gray')
ax[0, 0].set_title('Left Gray Image (cam0)')
ax[0, 1].imshow(dataset_gray[frame][1], cmap='gray')
ax[0, 1].set_title('Right Gray Image (cam1)')
ax[1, 0].imshow(dataset_rgb[frame][0])
ax[1, 0].set_title('Left RGB Image (cam2)')
ax[1, 1].imshow(dataset_rgb[frame][1])
ax[1, 1].set_title('Right RGB Image (cam3)')
plt.show()

points_step = int(1. / points)
point_size = 0.01 * (1. / points)
velo_range = range(0, dataset_velo[frame].shape[0], points_step)
velo_frame = dataset_velo[frame][velo_range, :]      
def draw_point_cloud(ax, title, axes=[0, 1, 2], xlim3d=None, ylim3d=None, zlim3d=None):
    """
    Convenient method for drawing various point cloud projections as a part of frame statistics.
    """
    ax.scatter(*np.transpose(velo_frame[:, axes]), s=point_size, c=velo_frame[:, 3], cmap='gray')
    ax.set_title(title)
    ax.set_xlabel('{} axis'.format(axes_str[axes[0]]))
    ax.set_ylabel('{} axis'.format(axes_str[axes[1]]))
    if len(axes) > 2:
        ax.set_xlim3d(*axes_limits[axes[0]])
        ax.set_ylim3d(*axes_limits[axes[1]])
        ax.set_zlim3d(*axes_limits[axes[2]])
        ax.set_zlabel('{} axis'.format(axes_str[axes[2]]))
    else:
        ax.set_xlim(*axes_limits[axes[0]])
        ax.set_ylim(*axes_limits[axes[1]])
    # User specified limits
    if xlim3d!=None:
        ax.set_xlim3d(xlim3d)
    if ylim3d!=None:
        ax.set_ylim3d(ylim3d)
    if zlim3d!=None:
        ax.set_zlim3d(zlim3d)
        
    for t_rects, t_type in zip(tracklet_rects[frame], tracklet_types[frame]):
        draw_box(ax, t_rects, axes=axes, color=colors[t_type])
        
# Draw point cloud data as 3D plot
f2 = plt.figure(figsize=(15, 8))
ax2 = f2.add_subplot(111, projection='3d')                    
draw_point_cloud(ax2, 'Velodyne scan', xlim3d=(-10,30))
plt.show()

# Draw point cloud data as plane projections
f, ax3 = plt.subplots(3, 1, figsize=(15, 25))
draw_point_cloud(
    ax3[0], 
    'Velodyne scan, XZ projection (Y = 0), the car is moving in direction left to right', 
    axes=[0, 2] # X and Z axes
)
draw_point_cloud(
    ax3[1], 
    'Velodyne scan, XY projection (Z = 0), the car is moving in direction left to right', 
    axes=[0, 1] # X and Y axes
)
draw_point_cloud(
    ax3[2], 
    'Velodyne scan, YZ projection (X = 0), the car is moving towards the graph plane', 
    axes=[1, 2] # Y and Z axes
)
plt.show() 


frame = 10

display_frame_statistics(dataset, tracklet_rects, tracklet_types, frame)

from source.utilities import print_progress
from moviepy.editor import ImageSequenceClip

def draw_3d_plot(frame, dataset, tracklet_rects, tracklet_types, points=0.2):
"""
Saves a single frame for an animation: a 3D plot of the lidar data without ticks and all frame trackelts.
Parameters
----------
frame : Absolute number of the frame.
dataset : raw dataset.
tracklet_rects : Dictionary with tracklet bounding boxes coordinates.
tracklet_types : Dictionary with tracklet types.
points : Fraction of lidar points to use. Defaults to 0.2, e.g. 20%.


Returns
-------
Saved frame filename.
"""
dataset_velo = list(dataset.velo)

f = plt.figure(figsize=(12, 8))
axis = f.add_subplot(111, projection='3d', xticks=[], yticks=[], zticks=[])

points_step = int(1. / points)
point_size = 0.01 * (1. / points)
velo_range = range(0, dataset_velo[frame].shape[0], points_step)
velo_frame = dataset_velo[frame][velo_range, :]
axis.scatter(*np.transpose(velo_frame[:, [0, 1, 2]]), s=point_size, c=velo_frame[:, 3], cmap='gray')
axis.set_xlim3d(*axes_limits[0])
axis.set_ylim3d(*axes_limits[1])
axis.set_zlim3d(*axes_limits[2])
for t_rects, t_type in zip(tracklet_rects[frame], tracklet_types[frame]):
    draw_box(axis, t_rects, axes=[0, 1, 2], color=colors[t_type])
filename = 'video/frame_{0:0>4}.png'.format(frame)
plt.savefig(filename)
plt.close(f)
return filename 


frames = []
n_frames = len(list(dataset.velo))

print('Preparing animation frames...')
for i in range(n_frames):
print_progress(i, n_frames - 1)
filename = draw_3d_plot(i, dataset, tracklet_rects, tracklet_types)
frames += [filename]
print('...Animation frames ready.')

clip = ImageSequenceClip(frames, fps=5)
% time
clip.write_gif('pcl_data.gif', fps=5)

**'2.kitti_readme'**

python
def compute_3d_box_cam2(h, w, l, x, y, z, yaw):
"""
Return : 3xn in cam2 coordinate
"""
R = np.array([[np.cos(yaw), 0, np.sin(yaw)], [0, 1, 0], [-np.sin(yaw), 0, np.cos(yaw)]])
x_corners = [l/2,l/2,-l/2,-l/2,l/2,l/2,-l/2,-l/2]
y_corners = [0,0,0,0,-h,-h,-h,-h]
z_corners = [w/2,-w/2,-w/2,w/2,w/2,-w/2,-w/2,w/2]
corners_3d_cam2 = np.dot(R, np.vstack([x_corners,y_corners,z_corners]))
corners_3d_cam2[0,:] += x
corners_3d_cam2[1,:] += y
corners_3d_cam2[2,:] += z
return corners_3d_cam2


**3.kitti_[frustum-pointnets](https://github.com/charlesq34/frustum-pointnets)#kitti的3D目标检测**

python
""" Helper methods for loading and parsing KITTI data.
Author: Charles R. Qi
Date: September 2017
"""
from __future__ import print_function
    
import numpy as np
import cv2
import os

class Object3d(object):
    ''' 3d object label '''
    def __init__(self, label_file_line):
        data = label_file_line.split(' ')
        data[1:] = [float(x) for x in data[1:]]

        # extract label, truncation, occlusion
        self.type = data[0] # 'Car', 'Pedestrian', ...
        self.truncation = data[1] # truncated pixel ratio [0..1]
        self.occlusion = int(data[2]) # 0=visible, 1=partly occluded, 2=fully occluded, 3=unknown
        self.alpha = data[3] # object observation angle [-pi..pi]

        # extract 2d bounding box in 0-based coordinates
        self.xmin = data[4] # left
        self.ymin = data[5] # top
        self.xmax = data[6] # right
        self.ymax = data[7] # bottom
        self.box2d = np.array([self.xmin,self.ymin,self.xmax,self.ymax])
        
        # extract 3d bounding box information
        self.h = data[8] # box height
        self.w = data[9] # box width
        self.l = data[10] # box length (in meters)
        self.t = (data[11],data[12],data[13]) # location (x,y,z) in camera coord.
        self.ry = data[14] # yaw angle (around Y-axis in camera coordinates) [-pi..pi]

    def print_object(self):
        print('Type, truncation, occlusion, alpha: %s, %d, %d, %f' % \
            (self.type, self.truncation, self.occlusion, self.alpha))
        print('2d bbox (x0,y0,x1,y1): %f, %f, %f, %f' % \
            (self.xmin, self.ymin, self.xmax, self.ymax))
        print('3d bbox h,w,l: %f, %f, %f' % \
            (self.h, self.w, self.l))
        print('3d bbox location, ry: (%f, %f, %f), %f' % \
            (self.t[0],self.t[1],self.t[2],self.ry))


class Calibration(object):
    ''' Calibration matrices and utils
        3d XYZ in <label>.txt are in rect camera coord.
        2d box xy are in image2 coord
        Points in <lidar>.bin are in Velodyne coord.
        y_image2 = P^2_rect * x_rect
        y_image2 = P^2_rect * R0_rect * Tr_velo_to_cam * x_velo
        x_ref = Tr_velo_to_cam * x_velo
        x_rect = R0_rect * x_ref
        P^2_rect = [f^2_u,  0,      c^2_u,  -f^2_u b^2_x;
                    0,      f^2_v,  c^2_v,  -f^2_v b^2_y;
                    0,      0,      1,      0]
                 = K * [1|t]
        image2 coord:
         ----> x-axis (u)
        |
        |
        v y-axis (v)
        velodyne coord:
        front x, left y, up z
        rect/ref camera coord:
        right x, down y, front z
        Ref (KITTI paper): http://www.cvlibs.net/publications/Geiger2013IJRR.pdf
        TODO(rqi): do matrix multiplication only once for each projection.
    '''
    def __init__(self, calib_filepath, from_video=False):
        if from_video:
            calibs = self.read_calib_from_video(calib_filepath)
        else:
            calibs = self.read_calib_file(calib_filepath)
        # Projection matrix from rect camera coord to image2 coord
        self.P = calibs['P2'] 
        self.P = np.reshape(self.P, [3,4])
        # Rigid transform from Velodyne coord to reference camera coord
        self.V2C = calibs['Tr_velo_to_cam']
        self.V2C = np.reshape(self.V2C, [3,4])
        self.C2V = inverse_rigid_trans(self.V2C)
        # Rotation from reference camera coord to rect camera coord
        self.R0 = calibs['R0_rect']
        self.R0 = np.reshape(self.R0,[3,3])

        # Camera intrinsics and extrinsics
        self.c_u = self.P[0,2]
        self.c_v = self.P[1,2]
        self.f_u = self.P[0,0]
        self.f_v = self.P[1,1]
        self.b_x = self.P[0,3]/(-self.f_u) # relative 
        self.b_y = self.P[1,3]/(-self.f_v)

    def read_calib_file(self, filepath):
        ''' Read in a calibration file and parse into a dictionary.
        Ref: https://github.com/utiasSTARS/pykitti/blob/master/pykitti/utils.py
        '''
        data = {}
        with open(filepath, 'r') as f:
            for line in f.readlines():
                line = line.rstrip()
                if len(line)==0: continue
                key, value = line.split(':', 1)
                # The only non-float values in these files are dates, which
                # we don't care about anyway
                try:
                    data[key] = np.array([float(x) for x in value.split()])
                except ValueError:
                    pass

        return data
    
    def read_calib_from_video(self, calib_root_dir):
        ''' Read calibration for camera 2 from video calib files.
            there are calib_cam_to_cam and calib_velo_to_cam under the calib_root_dir
        '''
        data = {}
        cam2cam = self.read_calib_file(os.path.join(calib_root_dir, 'calib_cam_to_cam.txt'))
        velo2cam = self.read_calib_file(os.path.join(calib_root_dir, 'calib_velo_to_cam.txt'))
        Tr_velo_to_cam = np.zeros((3,4))
        Tr_velo_to_cam[0:3,0:3] = np.reshape(velo2cam['R'], [3,3])
        Tr_velo_to_cam[:,3] = velo2cam['T']
        data['Tr_velo_to_cam'] = np.reshape(Tr_velo_to_cam, [12])
        data['R0_rect'] = cam2cam['R_rect_00']
        data['P2'] = cam2cam['P_rect_02']
        return data

    def cart2hom(self, pts_3d):
        ''' Input: nx3 points in Cartesian
            Oupput: nx4 points in Homogeneous by pending 1
        '''
        n = pts_3d.shape[0]
        pts_3d_hom = np.hstack((pts_3d, np.ones((n,1))))
        return pts_3d_hom
 
    # =========================== 
    # ------- 3d to 3d ---------- 
    # =========================== 
    def project_velo_to_ref(self, pts_3d_velo):
        pts_3d_velo = self.cart2hom(pts_3d_velo) # nx4
        return np.dot(pts_3d_velo, np.transpose(self.V2C))

    def project_ref_to_velo(self, pts_3d_ref):
        pts_3d_ref = self.cart2hom(pts_3d_ref) # nx4
        return np.dot(pts_3d_ref, np.transpose(self.C2V))

    def project_rect_to_ref(self, pts_3d_rect):
        ''' Input and Output are nx3 points '''
        return np.transpose(np.dot(np.linalg.inv(self.R0), np.transpose(pts_3d_rect)))
    
    def project_ref_to_rect(self, pts_3d_ref):
        ''' Input and Output are nx3 points '''
        return np.transpose(np.dot(self.R0, np.transpose(pts_3d_ref)))
 
    def project_rect_to_velo(self, pts_3d_rect):
        ''' Input: nx3 points in rect camera coord.
            Output: nx3 points in velodyne coord.
        ''' 
        pts_3d_ref = self.project_rect_to_ref(pts_3d_rect)
        return self.project_ref_to_velo(pts_3d_ref)

    def project_velo_to_rect(self, pts_3d_velo):
        pts_3d_ref = self.project_velo_to_ref(pts_3d_velo)
        return self.project_ref_to_rect(pts_3d_ref)

    # =========================== 
    # ------- 3d to 2d ---------- 
    # =========================== 
    def project_rect_to_image(self, pts_3d_rect):
        ''' Input: nx3 points in rect camera coord.
            Output: nx2 points in image2 coord.
        '''
        pts_3d_rect = self.cart2hom(pts_3d_rect)
        pts_2d = np.dot(pts_3d_rect, np.transpose(self.P)) # nx3
        pts_2d[:,0] /= pts_2d[:,2]
        pts_2d[:,1] /= pts_2d[:,2]
        return pts_2d[:,0:2]
    
    def project_velo_to_image(self, pts_3d_velo):
        ''' Input: nx3 points in velodyne coord.
            Output: nx2 points in image2 coord.
        '''
        pts_3d_rect = self.project_velo_to_rect(pts_3d_velo)
        return self.project_rect_to_image(pts_3d_rect)

    # =========================== 
    # ------- 2d to 3d ---------- 
    # =========================== 
    def project_image_to_rect(self, uv_depth):
        ''' Input: nx3 first two channels are uv, 3rd channel
                   is depth in rect camera coord.
            Output: nx3 points in rect camera coord.
        '''
        n = uv_depth.shape[0]
        x = ((uv_depth[:,0]-self.c_u)*uv_depth[:,2])/self.f_u + self.b_x
        y = ((uv_depth[:,1]-self.c_v)*uv_depth[:,2])/self.f_v + self.b_y
        pts_3d_rect = np.zeros((n,3))
        pts_3d_rect[:,0] = x
        pts_3d_rect[:,1] = y
        pts_3d_rect[:,2] = uv_depth[:,2]
        return pts_3d_rect

    def project_image_to_velo(self, uv_depth):
        pts_3d_rect = self.project_image_to_rect(uv_depth)
        return self.project_rect_to_velo(pts_3d_rect)

 
def rotx(t):
    ''' 3D Rotation about the x-axis. '''
    c = np.cos(t)
    s = np.sin(t)
    return np.array([[1,  0,  0],
                     [0,  c, -s],
                     [0,  s,  c]])


def roty(t):
    ''' Rotation about the y-axis. '''
    c = np.cos(t)
    s = np.sin(t)
    return np.array([[c,  0,  s],
                     [0,  1,  0],
                     [-s, 0,  c]])


def rotz(t):
    ''' Rotation about the z-axis. '''
    c = np.cos(t)
    s = np.sin(t)
    return np.array([[c, -s,  0],
                     [s,  c,  0],
                     [0,  0,  1]])


def transform_from_rot_trans(R, t):
    ''' Transforation matrix from rotation matrix and translation vector. '''
    R = R.reshape(3, 3)
    t = t.reshape(3, 1)
    return np.vstack((np.hstack([R, t]), [0, 0, 0, 1]))


def inverse_rigid_trans(Tr):
    ''' Inverse a rigid body transform matrix (3x4 as [R|t])
        [R'|-R't; 0|1]
    '''
    inv_Tr = np.zeros_like(Tr) # 3x4
    inv_Tr[0:3,0:3] = np.transpose(Tr[0:3,0:3])
    inv_Tr[0:3,3] = np.dot(-np.transpose(Tr[0:3,0:3]), Tr[0:3,3])
    return inv_Tr

def read_label(label_filename):
    lines = [line.rstrip() for line in open(label_filename)]
    objects = [Object3d(line) for line in lines]
    return objects

def load_image(img_filename):
    return cv2.imread(img_filename)

def load_velo_scan(velo_filename):
    scan = np.fromfile(velo_filename, dtype=np.float32)
    scan = scan.reshape((-1, 4))
    return scan

def project_to_image(pts_3d, P):
    ''' Project 3d points to image plane.
    Usage: pts_2d = projectToImage(pts_3d, P)
      input: pts_3d: nx3 matrix
             P:      3x4 projection matrix
      output: pts_2d: nx2 matrix
      P(3x4) dot pts_3d_extended(4xn) = projected_pts_2d(3xn)
      => normalize projected_pts_2d(2xn)
      <=> pts_3d_extended(nx4) dot P'(4x3) = projected_pts_2d(nx3)
          => normalize projected_pts_2d(nx2)
    '''
    n = pts_3d.shape[0]
    pts_3d_extend = np.hstack((pts_3d, np.ones((n,1))))
    print(('pts_3d_extend shape: ', pts_3d_extend.shape))
    pts_2d = np.dot(pts_3d_extend, np.transpose(P)) # nx3
    pts_2d[:,0] /= pts_2d[:,2]
    pts_2d[:,1] /= pts_2d[:,2]
    return pts_2d[:,0:2]


def compute_box_3d(obj, P):
    ''' Takes an object and a projection matrix (P) and projects the 3d
        bounding box into the image plane.
        Returns:
            corners_2d: (8,2) array in left image coord.
            corners_3d: (8,3) array in in rect camera coord.
    '''
    # compute rotational matrix around yaw axis
    R = roty(obj.ry)    

    # 3d bounding box dimensions
    l = obj.l;
    w = obj.w;
    h = obj.h;
    
    # 3d bounding box corners
    x_corners = [l/2,l/2,-l/2,-l/2,l/2,l/2,-l/2,-l/2];
    y_corners = [0,0,0,0,-h,-h,-h,-h];
    z_corners = [w/2,-w/2,-w/2,w/2,w/2,-w/2,-w/2,w/2];
    
    # rotate and translate 3d bounding box
    corners_3d = np.dot(R, np.vstack([x_corners,y_corners,z_corners]))
    #print corners_3d.shape
    corners_3d[0,:] = corners_3d[0,:] + obj.t[0];
    corners_3d[1,:] = corners_3d[1,:] + obj.t[1];
    corners_3d[2,:] = corners_3d[2,:] + obj.t[2];
    #print 'cornsers_3d: ', corners_3d 
    # only draw 3d bounding box for objs in front of the camera
    if np.any(corners_3d[2,:]<0.1):
        corners_2d = None
        return corners_2d, np.transpose(corners_3d)
    
    # project the 3d bounding box into the image plane
    corners_2d = project_to_image(np.transpose(corners_3d), P);
    #print 'corners_2d: ', corners_2d
    return corners_2d, np.transpose(corners_3d)


def compute_orientation_3d(obj, P):
    ''' Takes an object and a projection matrix (P) and projects the 3d
        object orientation vector into the image plane.
        Returns:
            orientation_2d: (2,2) array in left image coord.
            orientation_3d: (2,3) array in in rect camera coord.
    '''
    
    # compute rotational matrix around yaw axis
    R = roty(obj.ry)
   
    # orientation in object coordinate system
    orientation_3d = np.array([[0.0, obj.l],[0,0],[0,0]])
    
    # rotate and translate in camera coordinate system, project in image
    orientation_3d = np.dot(R, orientation_3d)
    orientation_3d[0,:] = orientation_3d[0,:] + obj.t[0]
    orientation_3d[1,:] = orientation_3d[1,:] + obj.t[1]
    orientation_3d[2,:] = orientation_3d[2,:] + obj.t[2]
    
    # vector behind image plane?
    if np.any(orientation_3d[2,:]<0.1):
      orientation_2d = None
      return orientation_2d, np.transpose(orientation_3d)
    
    # project orientation into the image plane
    orientation_2d = project_to_image(np.transpose(orientation_3d), P);
    return orientation_2d, np.transpose(orientation_3d)

def draw_projected_box3d(image, qs, color=(255,255,255), thickness=2):
    ''' Draw 3d bounding box in image
        qs: (8,3) array of vertices for the 3d box in following order:
            1 -------- 0
           /|         /|
          2 -------- 3 .
          | |        | |
          . 5 -------- 4
          |/         |/
          6 -------- 7
    '''
    qs = qs.astype(np.int32)
    for k in range(0,4):
       # Ref: http://docs.enthought.com/mayavi/mayavi/auto/mlab_helper_functions.html
       i,j=k,(k+1)%4
       # use LINE_AA for opencv3
       cv2.line(image, (qs[i,0],qs[i,1]), (qs[j,0],qs[j,1]), color, thickness, cv2.CV_AA)

       i,j=k+4,(k+1)%4 + 4
       cv2.line(image, (qs[i,0],qs[i,1]), (qs[j,0],qs[j,1]), color, thickness, cv2.CV_AA)

       i,j=k,k+4
       cv2.line(image, (qs[i,0],qs[i,1]), (qs[j,0],qs[j,1]), color, thickness, cv2.CV_AA)
    return image

3.oxts资料
GPS/IMU 3D localization unit
============================

The GPS/IMU information is given in a single small text file which is
written for each synchronized frame. Each text file contains 30 values
which are:

  - lat:     latitude of the oxts-unit (deg)
  - lon:     longitude of the oxts-unit (deg)
  - alt:     altitude of the oxts-unit (m)
  - roll:    roll angle (rad),  0 = level, positive = left side up (-pi..pi)
  - pitch:   pitch angle (rad), 0 = level, positive = front down (-pi/2..pi/2)
  - yaw:     heading (rad),     0 = east,  positive = counter clockwise (-pi..pi)
  - vn:      velocity towards north (m/s)
  - ve:      velocity towards east (m/s)
  - vf:      forward velocity, i.e. parallel to earth-surface (m/s)
  - vl:      leftward velocity, i.e. parallel to earth-surface (m/s)
  - vu:      upward velocity, i.e. perpendicular to earth-surface (m/s)
  - ax:      acceleration in x, i.e. in direction of vehicle front (m/s^2)
  - ay:      acceleration in y, i.e. in direction of vehicle left (m/s^2)
  - az:      acceleration in z, i.e. in direction of vehicle top (m/s^2)
  - af:      forward acceleration (m/s^2)
  - al:      leftward acceleration (m/s^2)
  - au:      upward acceleration (m/s^2)
  - wx:      angular rate around x (rad/s)
  - wy:      angular rate around y (rad/s)
  - wz:      angular rate around z (rad/s)
  - wf:      angular rate around forward axis (rad/s)
  - wl:      angular rate around leftward axis (rad/s)
  - wu:      angular rate around upward axis (rad/s)
  - posacc:  velocity accuracy (north/east in m)
  - velacc:  velocity accuracy (north/east in m/s)
  - navstat: navigation status
  - numsats: number of satellites tracked by primary GPS receiver
  - posmode: position mode of primary GPS receiver
  - velmode: velocity mode of primary GPS receiver
  - orimode: orientation mode of primary GPS receiver

To read the text file and interpret them properly an example is given in
the matlab folder: First, use oxts = loadOxtsliteData('2011_xx_xx_drive_xxxx')
to read in the GPS/IMU data. Next, use pose = convertOxtsToPose(oxts) to
transform the oxts data into local euclidean poses, specified by 4x4 rigid
transformation matrices. For more details see the comments in those files.

Coordinate Systems
==================

The coordinate systems are defined the following way, where directions
are informally given from the drivers view, when looking forward onto
the road:

  - Camera:   x: right,   y: down,  z: forward
  - Velodyne: x: forward, y: left,  z: up
  - GPS/IMU:  x: forward, y: left,  z: up

All coordinate systems are right-handed.

Sensor Calibration
==================

The sensor calibration zip archive contains files, storing matrices in
row-aligned order, meaning that the first values correspond to the first
row:

calib_cam_to_cam.txt: Camera-to-camera calibration
--------------------------------------------------

  - S_xx: 1x2 size of image xx before rectification
  - K_xx: 3x3 calibration matrix of camera xx before rectification
  - D_xx: 1x5 distortion vector of camera xx before rectification
  - R_xx: 3x3 rotation matrix of camera xx (extrinsic)
  - T_xx: 3x1 translation vector of camera xx (extrinsic)
  - S_rect_xx: 1x2 size of image xx after rectification
  - R_rect_xx: 3x3 rectifying rotation to make image planes co-planar
  - P_rect_xx: 3x4 projection matrix after rectification

Note: When using this dataset you will most likely need to access only
P_rect_xx, as this matrix is valid for the rectified image sequences.

calib_velo_to_cam.txt: Velodyne-to-camera registration
------------------------------------------------------

  - R: 3x3 rotation matrix
  - T: 3x1 translation vector
  - delta_f: deprecated
  - delta_c: deprecated

R|T takes a point in Velodyne coordinates and transforms it into the
coordinate system of the left video camera. Likewise it serves as a
representation of the Velodyne coordinate frame in camera coordinates.

calib_imu_to_velo.txt: GPS/IMU-to-Velodyne registration
-------------------------------------------------------

  - R: 3x3 rotation matrix
  - T: 3x1 translation vector

R|T takes a point in GPS/IMU coordinates and transforms it into the
coordinate system of the Velodyne scanner. Likewise it serves as a
representation of the GPS/IMU coordinate frame in Velodyne coordinates.

example transformations
-----------------------

As the transformations sometimes confuse people, here we give a short
example how points in the velodyne coordinate system can be transformed
into the camera left coordinate system.

In order to transform a homogeneous point X = [x y z 1]' from the velodyne
coordinate system to a homogeneous point Y = [u v 1]' on image plane of
camera xx, the following transformation has to be applied:

Y = P_rect_xx * R_rect_00 * (R|T)_velo_to_cam * X

To transform a point X from GPS/IMU coordinates to the image plane:

Y = P_rect_xx * R_rect_00 * (R|T)_velo_to_cam * (R|T)_imu_to_velo * X

The matrices are:

- P_rect_xx (3x4):         rectfied cam 0 coordinates -> image plane
- R_rect_00 (4x4):         cam 0 coordinates -> rectified cam 0 coord.
- (R|T)_velo_to_cam (4x4): velodyne coordinates -> cam 0 coordinates
- (R|T)_imu_to_velo (4x4): imu coordinates -> velodyne coordinates

Note that the (4x4) matrices above are padded with zeros and:
R_rect_00(4,4) = (R|T)_velo_to_cam(4,4) = (R|T)_imu_to_velo(4,4) = 1.

Tracklet Labels
===============

Tracklet labels are stored in XML and can be read / written using the 
C++/MATLAB source code provided with this development kit. For compiling
the code you will need to have a recent version of the boost libraries
installed.

Each tracklet is stored as a 3D bounding box of given height, width and
length, spanning multiple frames. For each frame we have labeled 3D location
and rotation in bird's eye view. Additionally, occlusion / truncation 
information is provided in the form of averaged Mechanical Turk label
outputs. All tracklets are represented in Velodyne coordinates.

Object categories are classified as following:

  - 'Car'
  - 'Van'
  - 'Truck'
  - 'Pedestrian'
  - 'Person (sitting)'
  - 'Cyclist'
  - 'Tram'
  - 'Misc'

Here, 'Misc' denotes all other categories, e.g., 'Trailers' or 'Segways'.

Reading the Tracklet Label XML Files
====================================

This toolkit provides the header 'cpp/tracklets.h', which can be used to
parse a tracklet XML file into the corresponding data structures. Its usage
is quite simple, you can directly include the header file into your code
as follows:

  #include "tracklets.h"
  Tracklets *tracklets = new Tracklets();
  if (!tracklets->loadFromFile(filename.xml))
    <throw an error>
  <do something with the tracklets>
  delete tracklets;

In order to compile this code you will need to have a recent version of the
boost libraries installed and you need to link against
'libboost_serialization'.

'matlab/readTrackletsMex.cpp' is a MATLAB wrapper for 'cpp/tracklets.h'.
It can be build using make.m. Again you need to link against
'libboost_serialization', which might be problematic on newer MATLAB
versions due to MATLAB's internal definitions of libstdc, etc. The latest
version which we know of which works on Linux is 2008b. This is because
MATLAB has changed its pointer representation.

Of course you can also directly parse the XML file using your preferred
XML parser. If you need to create another useful wrapper for the header file
(e.g., for Python) we would be more than happy if you could share it with us).

Demo Utility for projecting Tracklets into Images
=================================================

In 'matlab/run_demoTracklets.m' you find a demonstration script that reads
tracklets and projects them as 2D/3D bounding boxes into the images. You
will need to compile the MATLAB wrapper above in order to read the tracklets.
For further instructions, please have a look at the comments in the
respective MATLAB scripts and functions.

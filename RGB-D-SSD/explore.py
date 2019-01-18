"""
Parse ACTIVE VISION DATASET
"""

from data_generator.object_detection_2d_data_generator import DataGenerator

train_dataset = DataGenerator(load_images_into_memory=False, hdf5_dataset_path=None)
#val_dataset = DataGenerator(load_images_into_memory=False, hdf5_dataset_path=None)

# 2: Parse the image and label lists for the training and validation datasets. This can take a while.

# TODO: Set the paths to the datasets here.

# The directories that contain the images.
AVD_images_dir = '.../ActiveVisionDataset/example_scene/Home_003_1'
AVD_trainval_image_set_filename = '.../ActiveVisionDataset/example_scene/Home_003_1/jpg_rgb/train.txt'

Parse_Out = train_dataset.parse_AVD_json(images_dirs=[AVD_images_dir],
                        image_set_filenames=[AVD_trainval_image_set_filename],
                        ret=True)

print(Parse_Out)

"""
train_dataset.create_hdf5_dataset(file_path='dataset_AVD.h5',
                                  resize=False,
                                  variable_image_size=True,
                                  verbose=True)#"""

Here are some changed to the Keras SSD from Ferrari (https://github.com/pierluigiferrari/ssd_keras) in order to load the RGB-D images from the Active Vision Dataset (http://cs.unc.edu/~ammirato/active_vision_dataset_website/) into the SSD model

Copy the parse_AVD_json.py into object_detection_2d_data_generator.py next to the other parsers
Test it with explore.py
You can generate train.txt with split_train_val.py

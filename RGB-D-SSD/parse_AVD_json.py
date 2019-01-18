    def parse_AVD_json(self,
                  images_dirs,
                  image_set_filenames,
                  add_depth=False,
                  classes=[],
                  ret=False):
        '''
        This is an XML parser for the Active Vision datasets. It might be applicable to other datasets with minor changes to
        the code, but in its current form it expects the data format and JSON tag of the Active Vision datasets.

        Arguments:
            images_dirs (list): A list of strings, where each string is the path of a directory that
                contains images that are to be part of the dataset. This allows you to aggregate multiple datasets
                into one (e.g. one directory that contains the images for Home_003_1, another that contains
                the images for Home_003_2, etc.).
            image_set_filenames (list): A list of strings, where each string is the path of the text file with the image
                set to be loaded. Must be one file per image directory given. These text files define what images in the
                respective image directories are to be part of the dataset and simply contains one image ID per line
                and nothing else.
            classes (list, optional): A list containing the names of the object classes as found in the
                `name` XML tags. Must include the class `background` as the first list item. The order of this list
                defines the class IDs.
            include_classes (list, optional): Either 'all' or a list of integers containing the class IDs that
                are to be included in the dataset. If 'all', all ground truth boxes will be included in the dataset.
            ret (bool, optional): Whether or not to return the outputs of the parser.
            verbose (bool, optional): If `True`, prints out the progress for operations that may take a bit longer.

        Returns:
            None by default, optionally lists for whichever are available of images, image filenames, labels, image IDs,
            and a list indicating which boxes are annotated with the label "difficult".
        '''
        self.images_dirs = images_dirs
        self.add_depth = add_depth
        self.image_set_filenames = image_set_filenames,
        # Erase data that might have been parsed before.
        self.images = []
        self.filenames = []
        self.labels = []
        self.image_ids = []
        if len(classes)==0:
            # Set to default classes
            self.classes = ['background',
                            'advil_liqui_gels',
                            'aunt_jemima_original_syrup',
                            'bumblebee_albacore',
                            'cholula_chipotle_hot_sauce',
                            'coca_cola_glass_bottle',
                            'crest_complete_minty_fresh',
                            'crystal_hot_sauce',
                            'expo_marker_red',
                            'hersheys_bar',
                            'honey_bunches_of_oats_honey_roasted',
                            'honey_bunches_of_oats_with_almonds',
                            'hunts_sauce',
                            'listerine_green',
                            'mahatma_rice',
                            'nature_valley_granola_thins_dark_chocolate',
                            'nutrigrain_harvest_blueberry_bliss',
                            'pepto_bismol',
                            'pringles_bbq',
                            'progresso_new_england_clam_chowder',
                            'quaker_chewy_low_fat_chocolate_chunk',
                            'red_bull',
                            'softsoap_clear',
                            'softsoap_gold',
                            'softsoap_white',
                            'spongebob_squarepants_fruit_snaks',
                            'tapatio_hot_sauce',
                            'vo5_tea_therapy_healthful_green_tea_smoothing_shampoo',
                            'nature_valley_sweet_and_salty_nut_almond',
                            'nature_valley_sweet_and_salty_nut_cashew',
                            'nature_valley_sweet_and_salty_nut_peanut',
                            'nature_valley_sweet_and_salty_nut_roasted_mix_nut',
                            'paper_plate',
                            'red_cup']
        else:
            self.classes = classes

        # Iterate over all datasets.

        for images_dir, image_set_filename in zip(self.images_dirs,self.image_set_filenames):
            # Add Slash if missing
            if images_dir[-1] != '/':
                images_dir += '/'
            # Load the JSON file.
            annotations_filename = images_dir + 'annotations.json'
            with open(annotations_filename, 'r') as f:
                annotations = json.load(f)

            # Load Img IDs
            with open(image_set_filename[0]) as f: #zip() does not work as hoped unfortunately
                image_ids = [line.strip() for line in f] # Note: These are strings, not integers.
                self.image_ids += image_ids

            # Load Labels and Paths
            jpgpath = images_dir + 'jpg_rgb/'
            # Iterate over all images in dataset
            for image_id in image_ids:
                bboxes = []
                for bbox in annotations[image_id]['bounding_boxes']:
                    bboxes.append(bbox[:5]) # 4 bounding boxes coordinates + class (no difficulty)
                self.labels.append(bboxes)
                filepath = jpgpath + image_id
                self.filenames.append(filepath)

        if self.load_images_into_memory:
            self.images = []
            it = self.filenames
            for filename in it:
                with Image.open(filename) as image:
                    self.images.append(np.array(image, dtype=np.uint8))

        if ret:
            return self.images, self.filenames, self.labels, self.image_ids

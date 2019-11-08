import pandas as pd
import numpy as np


def clean_data(data_dir, save_dir, city_name=''):
    """
        This function cleans the raw data which was slightly manually modified and outputs a
    float data matrix with columns:
      year | month | date | time | temperature
    The output matrix will be save as .dat file at save_dir

    :param data_dir: str, directory to where the raw data is stored
    :param save_dir: str, directory to where the clean data wants to be stored
    :param city_name: str, city name
    """
    # read and convert the raw data into an array
    original_data = pd.read_csv(data_dir, delimiter=';')
    data = np.array(original_data[1:])

    # convert entries in the array to a string first
    for i in range(data.shape[0]):
        for j in range(data.shape[1]):
            data[i, j] = str(data[i, j])

    # clean column 0
    col0 = np.array([i.split('-') for i in data[:, 0]]).astype('int')

    # clean column 1
    #col1 = np.array([i.split(':') for i in data[:, 1]]).astype('int')
    #col1 = col1[:, 0]

    # clean column 2
    col2 = data[:, 2].astype('float')

    # concatenate the cleaned columns to a new matrix array
    #result = np.column_stack((np.column_stack((col0, col1)), col2))
    result = np.column_stack((col0, col2))

    # save the result to a specified dir
    save_dir = save_dir + city_name + '_clean.dat'
    np.savetxt(save_dir, result, fmt='%.1f')



save_dir = '/Users/apple/Desktop/'

# for Lund
data_dir0 = '/Users/apple/Desktop/smhi-opendata_Lund.csv'
clean_data(data_dir0, save_dir, 'lund')

# for Lulea
data_dir1 = '/Users/apple/Desktop/smhi-opendata_Lulea.csv'
clean_data(data_dir1, save_dir, 'lulea')

# for Umea
data_dir2 = '/Users/apple/Desktop/smhi-opendata_Umea.csv'
clean_data(data_dir2, save_dir, 'umea')

# for Visby
data_dir3 = '/Users/apple/Desktop/smhi-opendata_Visby.csv'
clean_data(data_dir3, save_dir, 'visby')

# for Uppsala which has a different format than the other ones
# output format: year | month | date | temperature
uppsala_data = np.loadtxt('/Users/apple/Desktop/uppsala_tm_1722-2013.dat')
clean_uppsala = np.column_stack((uppsala_data[:, 0:3], uppsala_data[:, 4]))
np.savetxt('/Users/apple/Desktop/uppsala_clean.dat', clean_uppsala, fmt='%.1f')
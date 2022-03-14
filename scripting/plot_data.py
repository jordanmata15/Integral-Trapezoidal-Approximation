import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import math
import os
import sys

path_to_script = os.path.dirname(__file__)

data_path = os.path.join(path_to_script, "../data") # data folder relative to this script
data_filename = os.path.join(data_path, "times.csv")


def crunch_data(filename):
    # num_threads, num_random_points, pi_approximation, time_elapsed
    df = pd.read_csv(filename)
    df["approximation_error"] = (abs(df["pi_approximation"]-math.pi)/math.pi) * 100

    # create our plots
    plot_threads_to_time(df[['num_threads','num_trapezoids', 'time_elapsed']])
    plot_points_to_accuracy(df[['approximation_error','num_trapezoids']])


"""
Plot number of threads to the time elapsed. One line for each data size. 
"""
def plot_threads_to_time(times_df):
    sizes = times_df["num_trapezoids"].unique()

    # format the plot
    fig, axs = plt.subplots(math.ceil(len(sizes)/2),2, constrained_layout=True)
    
    for ax in axs.flat:
        ax.set(xlabel='Number of Threads', ylabel='Time (seconds)')
    
    for ax,size in zip(axs.flat, sizes):
        local_df = times_df[times_df["num_trapezoids"] == size]
        x = local_df['num_threads']
        x_labels=[str(i) for i in x]
        y = local_df['time_elapsed']
        ax.set_title("Number of Trapezoids: " + str(size) +"^2", color="red")
        ax.plot(x_labels, y)

    fig.set_size_inches(18.5, 10.5)
    fig.savefig(os.path.join(data_path, "Plot_Threads_Time.pdf"), bbox_inches = "tight")


"""
Plot number of threads to the time elapsed. One line for each data size. 
"""
def plot_points_to_accuracy(times_df):
    df = times_df.groupby("num_trapezoids").mean()
    df.reset_index(inplace=True)

    # get x/y axis labels
    x = df['num_trapezoids']
    x_labels=[format(i, ",") for i in x]
    y = df['approximation_error']
    y_labels=[i for i in range(int(max(y)))]
    y_labels.append(int(max(y)))
    y_labels.append(int(max(y)+1))

    # set formatting
    fig, ax = plt.subplots(1,1)
    ax.set_ylim(ymin=0)
    ax.set_yticks(y_labels)
    plt.ylabel('Average Error (%)')
    ax.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
    plt.xticks(rotation=20)
    plt.xlabel('# Trapezoids')

    plt.grid()
    plt.autoscale()
    plt.plot(x_labels, y)
    plt.savefig(os.path.join(data_path, "Plot_Points_Accuracy.pdf"), bbox_inches = "tight")



if __name__=="__main__":
    if len(sys.argv) > 1:
        data_filename = sys.argv[1]

    file_full_path = os.path.join(path_to_script, data_filename)

    crunch_data(file_full_path)
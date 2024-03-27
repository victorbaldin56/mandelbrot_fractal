import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def read_files(files):
    ret = []
    for f in files:
        ret += [pd.read_csv(f)]
    return ret

def linear_plot(df, name):
    colors = ['red', 'green']
    labels = ['Dumb', 'AVX2']
    
    plt.figure(figsize=(7, 4))
    
    for i in range(labels.__len__()):
        plt.errorbar(df['N'], df[f'{labels[i]}'], xerr=0, yerr=0, 
                     fmt=f'{colors[i][0]}.')
        [a, b] = np.polyfit(df['N'], df[labels[i]], deg=1)
        z = np.linspace(0, max(df['N']), 1000)
        plt.plot(z, a * z + b, color=colors[i], label=labels[i])
         
    plt.grid(linestyle='--')
    plt.legend()
    plt.savefig(name)

dfs = read_files(['logs/no_optimization.csv', 'logs/with_optimization.csv'])
output_names = ['pictures/no_optimization.png',
                'pictures/with_optimization.png']

for i in range(dfs.__len__()):
    linear_plot(dfs[i], output_names[i])

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def read_files(files):
    ret = []
    for f in files:
        ret += [pd.read_csv(f)]
    return ret

def linear_plot(df, name, title):
    colors = ['red', 'green']
    labels = ['Dumb', 'AVX2']
    print(title)
    
    plt.figure(figsize=(7, 4))
    
    for i in range(labels.__len__()):
        plt.errorbar(df['N'], df[f'{labels[i]}'], xerr=0, yerr=0, 
                     fmt=f'{colors[i][0]}.')
        [a, b], cov = np.polyfit(df['N'], df[labels[i]], deg=1, cov=True)
        diag = np.diag(cov)
        diag = np.sqrt(diag)
        print(f'{labels[i]}: a = {a:.0f}, sigma = {diag[0]:.0f}')
        z = np.linspace(0, max(df['N']), 1000)
        plt.plot(z, a * z + b, color=colors[i], label=labels[i])
    
    plt.title(title)     
    plt.grid(linestyle='--')
    plt.legend()
    plt.xlabel('C')
    plt.ylabel('TSC')
    plt.savefig(name)

dfs = read_files(['logs/no_optimization.csv', 'logs/with_optimization.csv'])
output_names = ['pictures/no_optimization.png',
                'pictures/with_optimization.png']
titles = ['No optimization', 'With optimization']

for i in range(dfs.__len__()):
    linear_plot(dfs[i], output_names[i], titles[i])

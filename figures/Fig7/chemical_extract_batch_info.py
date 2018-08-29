import numpy as np
import glob
import pandas as pd
import matplotlib.pyplot as plt
from tqdm import tqdm

strength_files = sorted(glob.glob('./*/*/output.csv'))
identity_names = [x.split('/')[-2] for x in strength_files]

condition_names = [(x.split('Fig7/')[-1].split('/I=')[0]) for x in strength_files]
print(strength_files,condition_names)

colormap = plt.cm.nipy_spectral #nipy_spectral, Set1,Paired   
colors = [colormap(i) for i in np.linspace(1, 0,len(condition_names))]

sample_rate = 1000
sep='\t'

empty_df = pd.DataFrame()

plt.figure(figsize=(8,5.5),dpi=300)
plt.subplot(1,1,1)

for i,file in (enumerate(strength_files)):
	# if i%2==1:
	# 	continue
	df = pd.read_csv(file,sep=sep)
	empty_df[condition_names[i]] = (df['Values[AMPAR_bar]'])
	plt.plot(df.index[::sample_rate]/1000,df['Values[AMPAR_bar]'][::sample_rate],c=colors[i],label =condition_names[i],linewidth=3)
	#break1
plt.xticks(np.arange(0, 601, 100),fontsize=20,fontname="Arial")
plt.yticks(fontsize=20,fontname="Arial")
plt.xlim(xmin=0,xmax=600)
plt.xlabel('Simulation Time (s)',fontsize=22,fontname="Arial")
plt.ylabel('Activation ratio',fontsize=22,fontname="Arial" )#plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.legend()
plt.tight_layout()
plt.savefig('chem_figure_ampar.pdf')
empty_df['Time'] = empty_df.index/1000.0
empty_df.iloc[empty_df.index[::sample_rate]].to_csv('chem_scan.csv',index=False)



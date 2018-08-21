import numpy as np
import glob
import pandas as pd
import matplotlib.pyplot as plt
from tqdm import tqdm

strength_files = sorted(glob.glob('./Timing/*/outout.csv'))
identity_names = [x.split('/')[-2] for x in strength_files]

condition_names = [float(x.split('Timing=')[-1].split('_Normal')[0]) for x in identity_names]
sort_condition_names = sorted([x for x in condition_names if (float(x)>=-500) and (float(x)<=250)])
order = [condition_names.index(x) for x in sort_condition_names]
print(sort_condition_names)

colormap = plt.cm.gist_ncar #nipy_spectral, Set1,Paired   
colors = [colormap(i) for i in np.linspace(1, 0,len(sort_condition_names))]

sample_rate = 1000
sep=','

Ca_list = []
AMPAR_list = []
for i,file in (enumerate([strength_files[x] for x in order])):
	df = pd.read_csv(file,sep=',')
	Ca_list.append(np.mean(df['[Ca]']))
	AMPAR_list.append(df['Values[AMPAR_bar]'].values[-1])

output = np.stack(([int(x) for x in sort_condition_names],Ca_list,AMPAR_list),axis=-1)
np.savetxt('timing_ca_ampar.csv',output,fmt="%d,%e,%e", header='Hyperpolarisation timing (ms),Ca,AMPAR')




#print(len(strength_files),condition_names)

empty_df = pd.DataFrame()
plt.figure(figsize=(8,5.5),dpi=300)
plt.subplot(1,1,1)
colormap = plt.cm.gist_ncar #nipy_spectral, Set1,Paired   
colors = [colormap(i) for i in np.linspace(1, 0,len(sort_condition_names))]
sample_rate = 1000
for i,file in (enumerate([strength_files[x] for x in order])):
	if i%2==1:
		continue
	df = pd.read_csv(file,sep=sep)
	##empty_df[condition_names[i]] = (df['Values[AMPAR_bar]'])
	plt.plot(df.index[::sample_rate]/1000,df['Values[AMPAR_bar]'][::sample_rate],c=colors[i],label =sort_condition_names[i],linewidth=3)
	#break1
plt.xticks(np.arange(0, 601, 100),fontsize=20,fontname="Arial")
plt.yticks(np.arange(0.2, 0.51, 0.05),fontsize=20,fontname="Arial")
plt.xlim(xmin=0)
plt.xlabel('Simulation Time (s)',fontsize=22,fontname="Arial")
plt.ylabel('Activation ratio',fontsize=22,fontname="Arial" )#plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.tight_layout()
plt.savefig('timing_figure_ampar.pdf')



empty_df = pd.DataFrame()
plt.figure(figsize=(8,5.5),dpi=300)
plt.subplot(1,1,1)
for i,file in (enumerate([strength_files[x] for x in order])):
	if i%2==1:
		continue
	df = pd.read_csv(file,sep=sep)
	#empty_df[condition_names[i]] = (df['Values[CaMKII_active_ratio]'])
	plt.plot(df.index[::sample_rate]/1000,df['Values[CaMKII_active_ratio]'][::sample_rate],c=colors[i],label =sort_condition_names[i],linewidth=3)
	#break1
plt.xticks(np.arange(0, 601, 100),fontsize=20,fontname="Arial")
plt.yticks(np.arange(0., 0.81, 0.1),fontsize=20,fontname="Arial")
plt.xlim(xmin=0)
plt.xlabel('Simulation Time (s)',fontsize=22,fontname="Arial")
plt.ylabel('Activation ratio',fontsize=22,fontname="Arial" )#plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.tight_layout()
plt.savefig('timing_figure_camkii.pdf')


plt.figure(figsize=(8,5.5),dpi=300)
plt.subplot(1,1,1)
for i,file in (enumerate([strength_files[x] for x in order])):
	if i%2==1:
		continue
	df = pd.read_csv(file,sep=sep)
	#empty_df[condition_names[i]] = (df['Values[CaMKII_active_ratio]'])
	plt.plot(df.index[::sample_rate]/1000,df['Values[PP2B_bar]'][::sample_rate],c=colors[i],label =sort_condition_names[i],linewidth=1)
	#break1
plt.xticks(np.arange(0, 601, 100),fontsize=20,fontname="Arial")
plt.yticks(np.arange(0., 0.031, 0.005),fontsize=20,fontname="Arial")
plt.xlim(xmin=0)
plt.xlabel('Simulation Time (s)',fontsize=22,fontname="Arial")
plt.ylabel('Activation ratio',fontsize=22,fontname="Arial" )#plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.tight_layout()
plt.savefig('timing_figure_pp2b.pdf')



plt.figure(figsize=(8,5.5),dpi=300)
plt.subplot(1,1,1)

for i,file in (enumerate([strength_files[x] for x in order])):
	if i%2==1:
		continue
	df = pd.read_csv(file,sep=sep)
	plt.plot(df.index[::sample_rate]/1000,df['Values[PP1a_bar]'][::sample_rate],c=colors[i],label =sort_condition_names[i],linewidth=3)
plt.xticks(np.arange(0, 601, 100),fontsize=20,fontname="Arial")
plt.yticks(np.arange(0.1, 0.91, 0.1),fontsize=20,fontname="Arial")
plt.xlim(xmin=0)
plt.xlabel('Simulation Time (s)',fontsize=22,fontname="Arial")
plt.ylabel('Activation ratio',fontsize=22,fontname="Arial" )#plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.tight_layout()
plt.savefig('timing_figure_pp1a.pdf')


main = plt.figure(figsize=(8,5.5),dpi=300)
legend = plt.figure(figsize=(1.6,8.5 ),dpi=300)
ax = main.add_subplot(1,1,1)
plots = []
for i,file in (enumerate([strength_files[x] for x in order])):
	if i%2==1:
		continue
	#df = pd.read_csv(file,sep=sep)
	(ax.plot([1,1],[1,1],c=colors[i],label =str(int(sort_condition_names[i])) + ' ms',linewidth=3))

legend.legend(*ax.get_legend_handles_labels(),loc='center', frameon=False,fontsize=15,labelspacing=1.3)
legend.savefig('timing_legend.pdf')

# coding: utf-8

# In[2]:


import glob
import numpy as np


# In[4]:


copasi_duration_h = sorted(glob.glob('/home/ubuntu/MultiScale/Duration-H/*/*.cps'))


# In[21]:


strength_command = [x for x in copasi_duration_h]
print(len(strength_command))


# In[22]:


output = '/home/ubuntu/MultiScale/Duration-H/strength_command.txt'
with open(output, 'w') as OpenOutput:
    for line in strength_command:
        OpenOutput.writelines(line + '\n')


# In[6]:


copasi_strength= sorted(glob.glob('/home/ubuntu/MultiScale/Strength//*/*.cps'))
strength_command = [x for x in copasi_strength]
print(len(strength_command))


# In[7]:


output = '/home/ubuntu/MultiScale/Strength/strength_command.txt'
with open(output, 'w') as OpenOutput:
    for line in strength_command:
        OpenOutput.writelines(line + '\n')


# In[3]:


copasi_timing= sorted(glob.glob('/home/ubuntu/MultiScale/Timing_2/*/*.cps'))
timing_command = [x for x in copasi_timing]
print(len(timing_command))


# In[4]:


output = '/home/ubuntu/MultiScale/Timing_2/timing_command.txt'
with open(output, 'w') as OpenOutput:
    for line in timing_command:
        OpenOutput.writelines(line + '\n')


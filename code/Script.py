import numpy as np
import os.path
import subprocess
#path = r'C:\Users\user\Documents\GitHub\BRT_C_SE-2\code'
    
dirname = os.path.dirname(__file__)
# Conf = (8N, 8S, C50, D10, F14, G12, H13, H75, B13, B71, B12, B14, B10, B50, B75)
Conf = ([1,1,1,1,1,1,1,1,1,1,1,1,1,1,1])
Arreglos = []
contador = 0
while (contador<1):
    x1 = list(Conf)
    indice = np.random.choice(np.arange(len(Conf)))
    valor_nuevo = np.random.choice ([0,1,2,3,4,5])
    
    x1[indice] = valor_nuevo
    Conf = x1
    print(x1)
    if (x1[3]%2 !=0) and (x1[5]%2 != 0) and (x1[10]%2 != 0) and (x1[12]%2 != 0):
        
        if x1 not in Arreglos:
            Arreglos.append(x1)

            texto = f'0 100 2280 1001 1280 0 {x1[0]}\n'+f'1 2380 4560 3281 3560 1 {x1[1]}\n'+f'2 2380 4560 3281 3560 1 {x1[2]}\n'+f'3 2380 4560 3281 3560 1 {x1[3]}\n'+f'4 2380 4560 3281 3560 1 {x1[4]}\n'+f'5 2380 4560 3281 3560 1 {x1[5]}\n'+f'6 2380 4560 3281 3560 1 {x1[6]}\n'+f'7 2380 4560 3281 3560 1 {x1[7]}\n'+f'8 100 2280 1001 1280 0 {x1[8]}\n'+f'9 100 2280 1001 1280 0 {x1[9]}\n'+f'10 100 2280 1001 1280 0 {x1[10]}\n'+f'11 100 2280 1001 1280 0 {x1[11]}\n'+f'12 100 2280 1001 1280 0 {x1[12]}\n'+f'13 100 2280 1001 1280 0 {x1[13]}\n'+f'14 100 2280 1001 1280 0 {x1[14]}\n'+f'15 2380 4560 3281 3560\n'+f'16 100 2280 1001 1280'

            # ../conf
            #filename = os.path.relpath('..\conf\servicedefinition.txt', dirname)
            filename = os.path.join(dirname,'../conf/') + 'servicedefinition.txt'
            print(filename)
            f = open(filename,'w')
            f.write(texto)
            f.close()
            
            for i in range(4):
                procs = []
                for j in range(1,9):
                    seed= 10*i+j
                    command = ['./simulation','%i'%seed, '0']
                    procs.append(subprocess.Popen(command))
                    print(command)
                for process in procs:
                    process.wait()

            #for i in range(1,31):
                
                #subprocess.run(args=['simulation','%s'%i, '0'],cwd=dirname, shell=True)


            
        contador = contador + 1
#subprocess.run(['g++','-O2','simulation.cpp','-o','simulation.exe'], shell=True)



    




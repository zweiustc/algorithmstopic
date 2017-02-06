# Remove comments in c files like //  and /**/
# including comments after codes
#

global rfilename
rfilename ='./test.c'
global wfilename
wfilename = './w_test.c'

def clear_line_comments(item):
    if len(item) <= 2:
        return item

    flag = False
    for i in range(0, len(item)-1):
        if item[i] == '/' and item[i+1] == '/':
            flag = True
            break

    if flag and i > 0:
        return item[0:i-1]
    elif flag and i <= 0:
        return None
    else:
        return item

def detect_multi_line_comments(item):
    if len(item) <= 2:
        return 0 

    flag = 0 
    for i in range(0, len(item)-1):
        if item[i] == '/' and item[i+1] == '*':
            flag = 1 
            break

        if item[i] == '*' and item[i+1] == '/':
            flag = -1 
            break

    return int(flag)

if __name__ == '__main__':

    with open(rfilename, 'r') as fp:
        cnt = 0 
        for line in fp:
            line_new = clear_line_comments(line)
            ml_flag = detect_multi_line_comments(line_new)
            cnt =cnt + ml_flag
            if cnt > 0:
                continue
            if ml_flag == -1:
                continue

            if line_new is not None:
                with open(wfilename, 'a') as wfp:
                    wfp.write(line_new)
                    

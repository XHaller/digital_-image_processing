disp('�������ļ���')
str=input('please input a book name:','s')
f=imread(str); %�����ɫͼ��ע�ⲻ��ʹ�ûҶ�ͼ��
o=f;                %������ɫԭͼ
f=rgb2gray(f);     %����ɫͼ��ת��Ϊ�Ҷ�ͼ��
f=im2double(f);
figure();
imshow(f);

[m n] = size(f);

y  = f;
%�˲����õ�ͨ���ģ��
for i = 2: m-1
    for j = 2:n-1
        y(i,j) = (4*f(i,j) + f(i-1,j-1) + 2*f(i-1,j) + f(i-1,j+1) + 2*f(i,j-1) + 2*f(i,j+1) + f(i+1,j) + 2*f(i+1,j) + f(i+1,j+1))/16;
    end
end
figure();
imshow(y);

%����Ե����Sobel����




q = edge(y,'canny');
imshow(q);
size(q)
d = 3;
M = n*2/3;
z = zeros(1,round(m/d));
num = 0;
i = 1;
A = [];
while(i < m-40)
    count = 0;
    for k = 1:d
        for j = 1:n
            if q(i + k,j) ~= 0
                count = count +1;
            end
        end
    end
    if count > M
       num = num +1 ;
       A = [A,i];
       i = i + 40;
    else
        i = i + 1;
    end
end

X = 0;
l = f;
for i=3:m-2
    for j=3:n-2
        l(i,j)=-f(i-2,j)-f(i-1,j-1)-2*f(i-1,j)-f(i-1,j+1)-f(i,j-2)-2*f(i,j-1)+16*f(i,j)-2*f(i,j+1)-f(i,j+2)-f(i+1,j-1)-2*f(i+1,j)-f(i+1,j+1)-f(i+2,j);%LoG����
    end
end
figure();
imshow(l);

for  i = 1:A(1)
    for j = 1:n
        if  abs(f(i,j) - 0.45) > 0.2
            X =X +1;
        end
    end
end





if X/A(1)/n > 0.2
    num = num +1;
end
disp('ֱ������������');
A
disp('�鱾��Ŀ��');
num
        
  
        





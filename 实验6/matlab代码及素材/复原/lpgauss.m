function   Img = lpgauss(f)

sig = 2.0;

h=fspecial('gaussian',[7,7],sig);%��Ԥ�����gaussian����

[m n p]=size(f);

if p==1 %����Ҷ�ͼ��
    Img=double(f);
    Img=conv2(f,h,'same');%I��h�Ķ�ά��ɢ���
end
if p==3 %�������ɫ
    Img=double(f);
    Img(:,:,1)=conv2(f(:,:,1),h,'same');
    Img(:,:,2)=conv2(f(:,:,2),h,'same');
    Img(:,:,3)=conv2(f(:,:,3),h,'same');
end
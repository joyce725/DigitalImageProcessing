function g = intrans( f,varargin )
% g = intrans(f,'neg') 输出为输入图片的负片
%
% g = intrans(f,'log',c,class) 对图像进行log变换(公式为：g = c*log(1+double(f))),
%class为指定输出的图像类型，省略后两个参数时，c的默认值为1且输出默认为与输入图像图像类型一致
%
% g = intrans(f,'gamma',gam)
% 如果gam是小于1，该映射是偏重于高（亮）的输出值。如果gam大于1，该映射是偏向低（暗）的输出值。
%
% g = intrans(f,'stretch',m,E) 公式为（g =1./(1+(m./(f+eps)).^E)）。
% 可以不输人m与E，默认m为图像的平均值，e为E
% 对比度拉伸变换函数。该函数可以将输入值低于m的灰度级压缩为输出图像中较暗灰度级的较窄范围内；
% 类似的，可以将输入值高于m的灰度级压缩到为输出图像中较亮灰度级的较窄范围内。输出的是有较高对比度的图像。 
narginchk(2,4)
%判断正确的输入参量数目
classin=class(f);
if strcmp(class(f),'double') && max(f(:))>1 && ~strcmp(varargin{1},'log')
    f=matgray(f);
else 
    f=im2double(f);
end
%判断图像的类型，如果图像是double型，取值超出了[0,1]之外且转换方式不是对数转换就将范围转换至[0,1]间
%否则，转换成double型。
method=varargin{1};
switch method
    case 'neg'
       g=imcomplement(f);
    case 'log'
       if length(varargin)==1
           c=1;
       elseif length(varargin)==2
           c=varargin{2};
       elseif length(varargin)==3
           c=varargin{2};
           classin=varargin{3};
       else
           error('Incorrect number of inputs for the log option.')
       end
       g=c*(log(1+double(f)));
    case 'gamma'
       if length(varargin)<2
           error('Not enough inputs for the gamma option.')
       end
       gam=varargin{2};
       g=imadjust(f,[],[],gam);
    case 'stretch'
        if length(varargin)==1
            m=mean2(f);
            E=4.0;
        elseif length(varargin)==3
            m=varargin{2};
            E=varargin{3};
        else error('Incorrect number of inputs for the stretch option.')
        end
        g=1./(1+(m./(f+eps)).^E);
    otherwise
        error('Unkown enhancement method.')
    end
g=changeclass(classin, g);
%调用changeclass函数
end


#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights;
uniform SpotLight spotLight;
uniform Material material;


bool inRect(float,float,float,float);
void ledRectChar(int,float,float,float,float);
void showFloat(float);

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

     // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    // for(int i = 0; i < NR_POINT_LIGHTS; i++)
       result += CalcPointLight(pointLights, norm, FragPos, viewDir);    
       // vec3 result = CalcPointLight(pointLights, norm, FragPos, viewDir);    
    // phase 3: spot light
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
    // showFloat(material.shininess);
}


// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void showFloat(float f){
    int myNum[20];
    int k = 0;
    int iPart = int(floor(abs(f)));
    int fPart = int(fract(abs(f))*100000.0);
    float m=0.86;
    
    // 初始化数组,全部置为代表黑色的12
    for(int i=0; i<20; i++){
        myNum[i] = 12;
    }

    // 插入小数部分
    while (fPart>0)
    {   
        // 从个位开始, 依次取出个位,十位,百位,千位...的数字值
        myNum[k++]=fPart-((fPart/10)*10);
        fPart=fPart/10;
    }
    
    // 如果是0
    if(f==0.0){myNum[k++] = 0;}

    // 插入小数点
    myNum[k++] = 10;
    
    // 插入整数部分
    while (iPart>0)
    {   
        myNum[k++]=iPart-((iPart/10)*10);
        iPart=iPart/10;
    }
    
    // 如果是负数,则插入代表负号的11
    if(f<0.0) { myNum[k++]=11;}
   
    // 循环输出数字数组
    for(int i=0; i<20; i++)
    {
        m = m-0.03;
        ledRectChar(myNum[i], m, 0.02, 0.6, 0.15);
    }    
}

bool inRect(float x1,float x2, float y1, float y2){
    if(FragPos.x>x1 && FragPos.x<x2 && FragPos.y>y1 && FragPos.y<y2) 
    { return true; } else { return false; }
  return true;
}

void ledRectChar(int n, float xa,float xb, float ya, float yb){
    float x1 = xa; 
    float x2 = xa+xb;
    float y1 = ya;
    float y2 = ya+yb;
    float ox = (x2+x1)/2.0;
    float oy = (y2+y1)/2.0;
    float dx = (x2-x1)/10.0;
    float dy = (y2-y1)/10.0;
    float b = (x2-x1)/20.0;
    int num = n;
    
    // 设定调试区显示范围
    if(inRect(x1,x2,y1,y2)) {
        // 设置调试区背景色
        FragColor = vec4(0.2,1.0,0.2,1.0);
        // 分别绘制出 LED 形式的数字 1~0 , 用黑色绘制1个或2个矩形,由矩形以外的绿色区域组成字型
        if((num==1 && (inRect(x1,ox-dx,y1,y2) || inRect(ox+dx,x2,y1,y2))) ||
           (num==2 && (inRect(x1,x2-dx,oy+dy/2.0,y2-dy) || inRect(x1+dx,x2,y1+dy,oy-dy/2.0))) ||
           (num==3 && (inRect(x1,x2-dx,oy+dy/2.0,y2-dy) || inRect(x1,x2-dx,y1+dy,oy-dy/2.0))) ||
           (num==4 && (inRect(x1+dx,x2-dx,oy+dy/2.0,y2) || inRect(x1,x2-dx,y1,oy-dy/2.0))) ||
           (num==5 && (inRect(x1+dx,x2,oy+dy/2.0,y2-dy) || inRect(x1,x2-dx,y1+dy,oy-dy/2.0))) ||
           (num==6 && (inRect(x1+dx,x2,oy+dy/2.0,y2-dy) || inRect(x1+dx,x2-dx,y1+dy,oy-dy))) ||
           (num==7 && inRect(x1,x2-dx,y1,y2-dy)) ||
           (num==8 && (inRect(x1+dx,x2-dx,oy+dy/2.0,y2-dy) || inRect(x1+dx,x2-dx,y1+dy,oy-dy/2.0))) ||
           (num==9 && (inRect(x1+dx,x2-dx,oy+dy/2.0,y2-dy) || inRect(x1,x2-dx,y1+dy,oy-dy/2.0))) ||
           (num==0 && inRect(x1+dx,x2-dx,y1+dy,y2-dy)) ||
           // 传入10则绘制小数点, 传入11则绘制负号, 传入12则清空
           (num==10 && (inRect(x1,x2,oy-dy,y2) || inRect(x1,ox-dx*2.0,y1,oy-dy) || inRect(ox+dx*2.0,x2,y1,oy-dy) )) ||
           (num==11 && (inRect(x1,x2,oy+dy,y2) || inRect(x1,x2,y1,oy-dy))) ||
           (num==12)
          )
        {
            FragColor = vec4(0,0,0,.5);
        }       
    }
}
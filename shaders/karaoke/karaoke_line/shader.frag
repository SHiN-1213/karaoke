#version 330 core

const float M_PI  = 3.141592653589793;

in vec2 vertexPosition; // 入力頂点の位置
out vec4 FragColor;   // 出力色

uniform vec2 pointA;  // 点Aの位置
uniform vec2 pointB;  // 点Bの位置
uniform float lineWidth; // 直線の太さ
uniform float lineProgress;
uniform vec3 ourColor;

float dist(vec2 A_, vec2 B_)
{
    return sqrt((B_.x-A_.x)*(B_.x-A_.x)+(B_.y-A_.y)*(B_.y-A_.y));
}

float getRadian(vec2 A_, vec2 B_) {
    return atan(B_.y-A_.y, B_.x-A_.x);
}

void main()
{
    float dist_a = dist(vertexPosition,pointA);
    float dist_b = dist(vertexPosition,pointB);

    if(dist_a < dist_b)
    {
        float rad = getRadian(vertexPosition,pointA);
        if((M_PI/2 > rad && -M_PI/2 < rad) && dist_a > lineWidth/2)//pi/2 ~ 3/2pi
        {
            discard;
        }
    }
    else
    {
        float rad = getRadian(vertexPosition,pointB);
        if((M_PI/2 < rad || -M_PI/2 > rad) && dist_b > lineWidth/2)//pi/2 ~ 3/2pi
        {
            discard;
        }
    }

    FragColor = vec4(ourColor, 1.0);


}
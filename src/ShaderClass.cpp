#include "ShaderClass.h"

std::string get_file(const char* filename) {
    
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    } else {
        std::cerr << "Failed to load file name: " << filename << "\n";
        throw(errno);
    }
    
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    std::string vertexCode = get_file(vertexFile);
    std::string fragmentCode = get_file(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // create vertex shader object and its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // point vertex shader object to the vertex shader source
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    // create fragment shader object and its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // point fragment shader object to the fragment shader source
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    // create and get reference to program to link shaders
    ID = glCreateProgram();

    // attach vertex and fragment shaders to program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    // link shaders into program
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    // clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type) {
    GLint hasCompiled;
    char infoLog[1024];
    
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "SHADER_COMPILATION_ERROR for: " << type << "\n";
            std::cerr << infoLog << "\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "SHADER_LINKING_ERROR for: " << type << "\n";
            std::cerr << infoLog << "\n";
        }
    }
}
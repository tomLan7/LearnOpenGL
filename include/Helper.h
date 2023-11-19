#pragma once
#include<vector>
#include<string>
namespace lan {
    static EErrorType lanGetErrorOne() {
        GLenum error = glGetError();
            switch (error)
            {
            case GL_INVALID_ENUM:
                return EErrorType::INVALID_ENUM;
                break;
            case GL_INVALID_VALUE:
                return EErrorType::INVALID_VALUE;
                break;
            case GL_INVALID_OPERATION:
                return EErrorType::INVALID_OPERATION;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                //return EErrorType::INVALID_FRAMEBUFFER_OPERATION;
                break;
            case GL_OUT_OF_MEMORY:
                return EErrorType::OUT_OF_MEMORY;
                break;
            case GL_STACK_UNDERFLOW:
                //return EErrorType::STACK_UNDERFLOW;
                break;
            case GL_STACK_OVERFLOW:
                //return EErrorType::STACK_OVERFLOW;
                break;
            case GL_NO_ERROR:
                return EErrorType::NO_ERROR;
            default:
                break;
            }
            throw new std::exception("不支持的错误类型");
    }

    static std::vector<EErrorType> lanGetErrorList() {
        std::vector<EErrorType> rtnList;
        EErrorType error;
        do{
            error = lanGetErrorOne();
            rtnList.push_back(error);
        } while (error != EErrorType::NO_ERROR);

        return rtnList;
    }

    static std::string lanGetErrorStr(EErrorType error) {
        return (const char*)glewGetErrorString(Error2GLenum(error));
    }


    static std::string lanGetErrorStr(std::vector<EErrorType> errorList) {
        std::stringstream ss;
        for(auto error : errorList)
        {
            ss << "[" << lanGetErrorStr(error)<<"]";
        }
        return ss.str();
    }
}
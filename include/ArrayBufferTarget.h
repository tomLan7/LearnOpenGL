#pragma once
#include <GLBuffer.h>
#include"GLDef.h"
#include<vector>
#include"Vertex.h"
namespace lan {
    //代表了ArrayBuffer的Target上下文。可以加载缓冲对象或绘制等操作。集合一系列该操作
    class ArrayBufferTarget
    {
        static GLBuffer* current_buffer;
    public:
        static const ETarget_Type type = ETarget_Type::ARRAY_BUFFER;

        static void  BindBuffer(GLBuffer& buffer) {
            if (&buffer !=current_buffer) {
                current_buffer = &buffer;
                buffer.BindBuffer(type);
            }
        }
        static void  BindBuffer(GLBuffer* buffer) {
            if (buffer) {
                BindBuffer(*buffer);
            }
        }
        static void DrawArrays(GLenum mode,GLint first,GLsizei count) {
            glDrawArrays(mode, first, count);
        }


        ///绘制指定的buffer
        static void DrawArrays(GLBuffer* buffer, GLenum mode, GLint first, GLsizei count) {
            if (buffer) {
                auto backup = current_buffer;
                BindBuffer(buffer);
                DrawArrays(mode, first, count);
                if (backup != buffer) {
                    BindBuffer(backup);
                }
            }
        }

        /// <summary>
        /// 往target和Usage_Type所对应的目标内存传输数据。
        /// </summary>
        /// <param name="target"></param>
        /// <param name="data"></param>
        /// <param name="len"></param>
        /// <param name="usage"></param>
        static void BufferData(size_t len, const void* data, EUsage_Type usage) {
            glBufferData(Target2GLenum(type), len, data, Usage2GLenum(usage));
        }

        static void BufferData(GLBuffer* buffer, size_t len, const void* data, EUsage_Type usage) {
            if (buffer) {
                    auto backup = current_buffer;
                    BindBuffer(buffer);
                    glBufferData(Target2GLenum(type), len, data, Usage2GLenum(usage));
                    if (backup != buffer) {
                        BindBuffer(backup);
                    }
            }
        }
        static void BufferData(GLBuffer* buffer, std::vector<Vertex>& vertices, EUsage_Type usage) {
            BufferData(buffer, vertices.size()* sizeof(Vertex), vertices.data(),usage);
        }
    };
}
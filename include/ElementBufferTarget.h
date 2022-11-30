#pragma once
#include <GLBuffer.h>
#include"GLDef.h"
namespace lan {
    //代表了ArrayBuffer的Target上下文。可以加载缓冲对象或绘制等操作。集合一系列该操作
    class ElementBufferTarget
    {
        static GLBuffer* current_buffer;
    public:
        static const Target_Type type = Target_Type::ELEMENT_ARRAY_BUFFER;

        static void  BindBuffer(GLBuffer& buffer) {
            if (&buffer != current_buffer) {
                current_buffer = &buffer;
                buffer.BindBuffer(type);
            }
        }

        static void  BindBuffer(GLBuffer* buffer) {
            if (buffer) {
                BindBuffer(*buffer);
            }
        }

        static void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
            glDrawElements(mode, count, type, indices);
        }


        ///绘制指定的buffer
        static void DrawElements(GLBuffer* buffer, GLenum mode, GLsizei count, GLenum type, const void* indices) {
            if (buffer) {
                auto backup = current_buffer;
                BindBuffer(buffer);
                DrawElements(mode, count, type, indices);
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
        static void BufferData(size_t len, const void* data, Usage_Type usage) {
            glBufferData(Target2GLenum(type), len, data, Usage2GLenum(usage));
        }

        static void BufferData(GLBuffer* buffer, size_t len, const void* data, Usage_Type usage) {
            if (buffer) {
                auto backup = current_buffer;
                BindBuffer(buffer);
                BufferData(len, data,usage);
                if (backup != buffer) {
                    BindBuffer(backup);
                }
            }
        }
    };
}


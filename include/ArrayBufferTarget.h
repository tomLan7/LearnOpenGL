#pragma once
#include <GLBuffer.h>
#include"GLDef.h"
namespace lan {
    //������ArrayBuffer��Target�����ġ����Լ��ػ���������ƵȲ���������һϵ�иò���
    class ArrayBufferTarget
    {
        static GLBuffer* current_buffer;
    public:
        static const Target_Type type = Target_Type::ARRAY_BUFFER;

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


        ///����ָ����buffer
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
        /// ��target��Usage_Type����Ӧ��Ŀ���ڴ洫�����ݡ�
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
                    glBufferData(Target2GLenum(type), len, data, Usage2GLenum(usage));
                    if (backup != buffer) {
                        BindBuffer(backup);
                    }
            }
        }
    };
}


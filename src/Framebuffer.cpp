//
// Created by Brandon Boudreaux on 3/24/23.
//

#include "Framebuffer.h"

Expression::Framebuffer::Framebuffer(ImVec2 s) {
    size = s;

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, size.x, size.y, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "The frame buffer is not complete!" << std::endl;
        return;
    }

    UnBindFBO();
    UnBindRBO();
    UnBindTex();
}

Expression::Framebuffer::~Framebuffer() {
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &tex);
}

void Expression::Framebuffer::SetSize(ImVec2 s) {

    size = s;

    BindFBO();
    BindTex();
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, size.x, size.y, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    BindRBO();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "The frame buffer is not complete!" << std::endl;
        return;
    }

    UnBindFBO();
    UnBindRBO();
    UnBindTex();
}

GLuint Expression::Framebuffer::GetTexture() {
    return tex;
}

ImVec2 Expression::Framebuffer::GetSize() {
    return size;
}
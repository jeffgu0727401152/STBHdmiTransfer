/*=============================================================================
Copyright (c) 2012 Broadcom Europe Limited.
All rights reserved.

Project  :  khronos
Module   :  Broadcom GLES extensions header

FILE DESCRIPTION
Extensions which we invented. Included by gl_public_api.h (used in the driver).
If applications want to use these they must include this file explicitly.
=============================================================================*/

#ifndef GL3EXT_BRCM_H
#define GL3EXT_BRCM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

/*  http://www.opengl.org/registry/api/enum.spec                              */
/*                                                                            */
/*  If an extension is experimental, allocate temporary enum values in the    */
/*  range 0x6000-0x8000 during development work.  When the vendor commits to  */
/*  releasing the extension, allocate permanent enum values (see link).       */

/* Expose "mirror once" and "clamp to border" texture wrap modes */
#ifndef GL_BRCM_mirror_once_border
#define GL_BRCM_mirror_once_border 1
#endif
#if GL_BRCM_mirror_once_border
#define GL_CLAMP_TO_BORDER_BRCM        0x7900   /* wrap mode */
#define GL_MIRROR_ONCE_BRCM            0x7901   /* wrap mode */
#define GL_TEXTURE_BORDER_COLOR_BRCM   0x7902   /* glTexParameterfv pname */
#endif

/* Expose texture flip x, flip y and swap st */
#ifndef GL_BRCM_texture_mirror_swap
#define GL_BRCM_texture_mirror_swap 1
#endif
#if GL_BRCM_texture_mirror_swap
#define GL_TEXTURE_FLIP_X              0x7910 /* mirror x */
#define GL_TEXTURE_FLIP_Y              0x7911 /* mirror y */
#define GL_TEXTURE_SWAP_ST             0x7912 /* swap st */
#endif

/* Expose unorm16/snorm16 texture types */
#ifndef GL_BRCM_texture_norm16
#define GL_BRCM_texture_norm16 1
#endif
#if GL_BRCM_texture_norm16
/* or we could try and reuse GL_R16 etc.? */
#define GL_R16_BRCM                   0x7920
#define GL_RG16_BRCM                  0x7921
#define GL_RGBA16_BRCM                0x7922
#define GL_R16_SNORM_BRCM             0x7923
#define GL_RG16_SNORM_BRCM            0x7924
#define GL_RGBA16_SNORM_BRCM          0x7925
#endif

#ifndef GL_BRCM_texture_1D
#define GL_BRCM_texture_1D 1
#endif
#if GL_BRCM_texture_1D
#define GL_TEXTURE_1D_BRCM               0x7930
#define GL_TEXTURE_1D_ARRAY_BRCM         0x7931
#define GL_SAMPLER_1D_BRCM               0x7932
#define GL_SAMPLER_1D_ARRAY_BRCM         0x7933
#define GL_INT_SAMPLER_1D_BRCM           0x7934
#define GL_INT_SAMPLER_1D_ARRAY_BRCM     0x7935
#define GL_UNSIGNED_INT_SAMPLER_1D_BRCM        0x7936
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_BRCM  0x7937
#define GL_TEXTURE_BINDING_1D_BRCM       0x7938
#define GL_TEXTURE_BINDING_1D_ARRAY_BRCM 0x7939

#ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glTexImage1DBRCM (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
#endif
typedef void   (GL_APIENTRYP PFNGLTEXIMAGE1DBRCMPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
#endif /* GL_BRCM_texture_1D */

/*  Features for V3D v. 3.1 / OpenGL ES 3.1     */

/*  BRCM_multi_draw_indirect / ARB_multi_draw_indirect / OpenGL 4.3  */

#ifndef GL_BRCM_multi_draw_indirect
# define GL_BRCM_multi_draw_indirect 1
#endif
#if GL_BRCM_multi_draw_indirect
typedef void (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTBRCMPROC) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTBRCMPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);

#ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glMultiDrawArraysIndirectBRCM (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
GL_APICALL void GL_APIENTRY glMultiDrawElementsIndirectBRCM (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
#endif
#endif /* GL_BRCM_multi_draw_indirect */

/*  BRCM_base_instance / ARB_base_instance / OpenGL 4.2  */

#ifndef GL_BRCM_base_instance
# define GL_BRCM_base_instance 1
#endif
#if GL_BRCM_base_instance
typedef void (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEBRCMPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEBRCMPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
typedef void (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEBRCMPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);

#ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glDrawArraysInstancedBaseInstanceBRCM (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
GL_APICALL void GL_APIENTRY glDrawElementsInstancedBaseInstanceBRCM (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL void GL_APIENTRY glDrawElementsInstancedBaseVertexBaseInstanceBRCM (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#endif
#endif /* GL_BRCM_base_instance */

#ifndef GL_BRCM_polygon_mode
#define GL_BRCM_polygon_mode 1
#endif
#if GL_BRCM_polygon_mode
#define GL_FILL_BRCM    0x1B02 // These share values with the non-BRCM versions in gl3.h
#define GL_LINE_BRCM    0x1B01
#define GL_POINT_BRCM   0x1B00
#ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glPolygonModeBRCM(GLenum mode);
#endif
#endif /* GL_BRCM_polygon_mode */

/* Like https://www.opengl.org/registry/specs/EXT/provoking_vertex.txt */
#ifndef GL_BRCM_provoking_vertex
# define GL_BRCM_provoking_vertex 1
#endif
#if GL_BRCM_provoking_vertex
#define GL_FIRST_VERTEX_CONVENTION_BRCM   0x8E4D
#define GL_LAST_VERTEX_CONVENTION_BRCM    0x8E4E
#define GL_PROVOKING_VERTEX_BRCM          0x8E4F
typedef void (GL_APIENTRYP PFNGLPROVOKINGVERTEXBRCMPROC)(GLenum mode);
#ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glProvokingVertexBRCM(GLenum mode);
#endif
#endif /* GL_BRCM_provoking_vertex */

#ifndef GL_BRCM_texture_unnormalised_coords
# define GL_BRCM_texture_unnormalised_coords 1
#endif
#if GL_BRCM_texture_unnormalised_coords
#define GL_TEXTURE_UNNORMALISED_COORDS_BRCM 0x7940
#endif /*GL_BRCM_texture_unnormalised_coords */

#ifdef __cplusplus
}
#endif

#endif

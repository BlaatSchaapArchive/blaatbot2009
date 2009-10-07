#ifndef _FUNCTION_POINTER_TYPES_
#define _FUNCTION_POINTER_TYPES_
     
#define t_f_pcar_v const char * (*)(void)
#define t_f_v_v            void (*)(void)
#define t_f_pv_pv        void * (*)(void *)
#define t_f_i_pv            int (*)(void *)
#define t_f_i_pchar         int (*)(const char *)
#define t_f_v_pchar        void (*)(const char *)
#define t_f_v_4pchar_1i    void (*)(const char *, const char *, const char *, int)
#define t_f_v_4pchar       void (*)(const char *, const char *, const char *, const char *)
#define t_f_v_5pchar       void (*)(const char *, const char *, const char *, const char *, const char *)
#define t_f_v_6pchar       void (*)(const char *, const char *, const char *, const char *, const char *, const char *)
#define t_f_v_7pchar       void (*)(const char *, const char *, const char *, const char *, const char *, const char *, const char *)
#define t_f_i_8pchar        int (*)(const char* , const char*,  const char*,  const char*,  const char*,  const char*,  const char*, const char*) 



#define t_f_pcar_v const char * (*)(void)
#define t_f_v_v            void (*)(void)
#define t_f_pv_pv        void * (*)(void *)
#define t_f_i_pv            int (*)(void *)
#define t_f_i_pchar         int (*)(const char *)
#define t_f_v_pchar        void (*)(const char *)
#define t_f_v_4pchar_1i    void (*)(const char *, const char *, const char *, int)



#define t_f_v_pv              void (*)(void *)
#define t_f_v_1pv2pchar       void (*)(void *, const char *, const char *)
#define t_f_v_1pv3pchar       void (*)(void *, const char *, const char *, const char *)
#define t_f_v_1pv4pchar       void (*)(void *, const char *, const char *, const char *, const char *)
#define t_f_v_1pv5pchar       void (*)(void *, const char *, const char *, const char *, const char *, const char *)
#define t_f_v_1pv6pchar       void (*)(void *, const char *, const char *, const char *, const char *, const char *, const char *)
#define t_f_v_1pv7pchar       void (*)(void *, const char *, const char *, const char *, const char *, const char *, const char *, const char *)


#define t_f_b_4pchar          bool(*)(const char*, const char*, const  char*, const  char*)
#define t_f_b_5pchar          bool(*)(const char*, const char*, const  char*, const  char*, const  char*)

#define t_f_i_i_vp            int(*)(int, void *)

#endif

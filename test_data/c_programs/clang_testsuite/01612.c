typedef unsigned int v2u __attribute__ ((vector_size (8)));
typedef int v2s __attribute__ ((vector_size (8)));
typedef float v2f __attribute__ ((vector_size(8)));
void test1(v2u v2ua, v2s v2sa, v2f v2fa) {
  (void)(v2ua & v2ua);
  (void)(v2fa & v2fa);
  (void)(~v2ua);
  (void)(~v2fa);
  v2ua = (v2ua==v2sa);
  v2sa = (v2ua==v2sa);
  int array1[v2ua];
  int array2[17];
  (void)(array2[v2ua]);
  v2u *v2u_ptr = 0;
  v2s *v2s_ptr;
  v2s_ptr = v2u_ptr;
}
void testLogicalVecVec(v2u v2ua, v2s v2sa, v2f v2fa) {
  v2ua = v2ua && v2ua;
  v2ua = v2ua || v2ua;
  v2ua = v2sa && v2ua;
  v2ua = v2sa || v2ua;
  v2ua = v2ua && v2fa;
  v2ua = v2ua || v2fa;
  v2ua = v2sa && v2fa;
  v2ua = v2sa || v2fa;
  v2sa = v2sa && v2sa;
  v2sa = v2sa || v2sa;
  v2sa = v2ua && v2ua;
  v2sa = v2ua || v2ua;
  v2sa = v2sa && v2ua;
  v2sa = v2sa || v2ua;
  v2sa = v2sa && v2fa;
  v2sa = v2sa || v2fa;
  v2sa = v2ua && v2fa;
  v2sa = v2ua || v2fa;
  v2fa = v2fa && v2fa;
  v2fa = v2fa || v2fa;
  v2fa = v2sa && v2fa;
  v2fa = v2sa || v2fa;
  v2fa = v2ua && v2fa;
  v2fa = v2ua || v2fa;
  v2fa = v2ua && v2ua;
  v2fa = v2ua || v2ua;
  v2fa = v2sa && v2sa;
  v2fa = v2sa || v2sa;
  v2fa = v2sa && v2ua;
  v2fa = v2sa || v2ua;
}
void testLogicalVecScalar(v2u v2ua, v2s v2sa, v2f v2fa) {
  unsigned u1;
  v2ua = v2ua && u1;
  v2ua = v2ua || u1;
  v2sa = v2sa && u1;
  v2sa = v2sa || u1;
  v2ua = v2sa && u1;
  v2ua = v2sa || u1;
  v2sa = v2ua && u1;
  v2sa = v2ua || u1;
  v2ua = v2fa && u1;
  v2ua = v2fa || u1;
  v2sa = v2fa && u1;
  v2sa = v2fa || u1;
  int s1;
  v2ua = v2ua && s1;
  v2ua = v2ua || s1;
  v2sa = v2sa && s1;
  v2sa = v2sa || s1;
  v2ua = v2sa && s1;
  v2ua = v2sa || s1;
  v2sa = v2ua && s1;
  v2sa = v2ua || s1;
  v2ua = v2fa && s1;
  v2ua = v2fa || s1;
  v2sa = v2fa && s1;
  v2sa = v2fa || s1;
  float f1;
  v2ua = v2ua && f1;
  v2ua = v2ua || f1;
  v2sa = v2sa && f1;
  v2sa = v2sa || f1;
  v2ua = v2sa && f1;
  v2ua = v2sa || f1;
  v2sa = v2ua && f1;
  v2sa = v2ua || f1;
  v2ua = v2fa && f1;
  v2ua = v2fa || f1;
  v2sa = v2fa && f1;
  v2sa = v2fa || f1;
}

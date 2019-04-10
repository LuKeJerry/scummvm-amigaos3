# d e f i n e   A p p N a m e   " S c u m m V M " 
 # d e f i n e   F i l e V e r s i o n = G e t F i l e V e r s i o n ( ' s c u m m v m . e x e ' )   
 # d e f i n e   P r o d u c t V e r s i o n = G e t S t r i n g F i l e I n f o ( ' s c u m m v m . e x e ' ,   ' P r o d u c t V e r s i o n ' ) 
 # d e f i n e   C o p y r i g h t = G e t S t r i n g F i l e I n f o ( ' s c u m m v m . e x e ' ,   ' L e g a l C o p y r i g h t ' ) 
 
 [ S e t u p ] 
 A p p C o p y r i g h t = { # C o p y r i g h t } 
 A p p N a m e = { # A p p N a m e } 
 A p p V e r s i o n = { # P r o d u c t V e r s i o n } 
 V e r s i o n I n f o V e r s i o n = { # F i l e V e r s i o n } 
 A p p V e r N a m e = { # A p p N a m e }   { # P r o d u c t V e r s i o n } 
 A p p P u b l i s h e r = T h e   S c u m m V M   T e a m 
AppPublisherURL=https://www.scummvm.org/
AppSupportURL=https://www.scummvm.org/
AppUpdatesURL=https://www.scummvm.org/
 D e f a u l t D i r N a m e = { p f } \ { # A p p N a m e } 
 D e f a u l t G r o u p N a m e = { # A p p N a m e } 
 A l l o w N o I c o n s = t r u e 
 A l w a y s U s e P e r s o n a l G r o u p = f a l s e 
 E n a b l e D i r D o e s n t E x i s t W a r n i n g = f a l s e 
 C o m p r e s s i o n = l z m a 2 / u l t r a 
 O u t p u t D i r = C : \ { # A p p N a m e } 
 O u t p u t B a s e F i l e n a m e = s c u m m v m - w i n 3 2 
 D i s a b l e S t a r t u p P r o m p t = t r u e 
 A p p e n d D e f a u l t D i r N a m e = f a l s e 
 S o l i d C o m p r e s s i o n = t r u e 
 D i r E x i s t s W a r n i n g = n o 
 S e t u p I c o n F i l e = g r a p h i c s \ s c u m m v m - i n s t a l l . i c o 
 U n i n s t a l l D i s p l a y I c o n = { a p p } \ s c u m m v m . e x e 
 W i z a r d I m a g e F i l e = g r a p h i c s \ l e f t . b m p 
 W i z a r d S m a l l I m a g e F i l e = g r a p h i c s \ s c u m m v m - i n s t a l l . b m p 
 S h o w L a n g u a g e D i a l o g = y e s 
 L a n g u a g e D e t e c t i o n M e t h o d = u i l a n g u a g e 
 P r i v i l e g e s R e q u i r e d = n o n e 
 D i s a b l e W e l c o m e P a g e = F a l s e 
 
 
 ;   T h i s   p r i v i l e g e   e s c a l a t i o n   c o d e   c o m e s   f r o m 
 ;   h t t p s : / / s t a c k o v e r f l o w . c o m / a / 3 5 4 3 5 5 3 4 / 2 5 2 0 8 7 
 
 # d e f i n e   I n n o S e t u p R e g   \ 
     " S o f t w a r e \ M i c r o s o f t \ W i n d o w s \ C u r r e n t V e r s i o n \ U n i n s t a l l \ "   +   A p p N a m e   +   " _ i s 1 " 
 # d e f i n e   I n n o S e t u p A p p P a t h R e g   " I n n o   S e t u p :   A p p   P a t h " 
 
 [ C o d e ] 
 f u n c t i o n   I s W i n V i s t a :   B o o l e a n ; 
 b e g i n 
     R e s u l t   : =   ( G e t W i n d o w s V e r s i o n   > =   $ 0 6 0 0 0 0 0 0 ) ; 
 e n d ; 
 
 f u n c t i o n   I s E l e v a t e d :   B o o l e a n ; 
 b e g i n 
     R e s u l t   : =   I s A d m i n L o g g e d O n   o r   I s P o w e r U s e r L o g g e d O n ; 
 e n d ; 
 
 f u n c t i o n   H a v e W r i t e A c c e s s T o A p p :   B o o l e a n ; 
 v a r 
     F i l e N a m e :   s t r i n g ; 
 b e g i n 
     F i l e N a m e   : =   A d d B a c k s l a s h ( W i z a r d D i r V a l u e )   +   ' w r i t e t e s t . t m p ' ; 
     R e s u l t   : =   S a v e S t r i n g T o F i l e ( F i l e N a m e ,   ' t e s t ' ,   F a l s e ) ; 
     i f   R e s u l t   t h e n 
     b e g i n 
         L o g ( F o r m a t ( 
             ' H a v e   w r i t e   a c c e s s   t o   t h e   l a s t   i n s t a l l a t i o n   p a t h   [ % s ] ' ,   [ W i z a r d D i r V a l u e ] ) ) ; 
         D e l e t e F i l e ( F i l e N a m e ) ; 
     e n d 
         e l s e 
     b e g i n 
         L o g ( F o r m a t ( ' D o e s   n o t   h a v e   w r i t e   a c c e s s   t o   t h e   l a s t   i n s t a l l a t i o n   p a t h   [ % s ] ' ,   [ 
             W i z a r d D i r V a l u e ] ) ) ; 
     e n d ; 
 e n d ; 
 
 p r o c e d u r e   E x i t P r o c e s s ( u E x i t C o d e :   U I N T ) ; 
     e x t e r n a l   ' E x i t P r o c e s s @ k e r n e l 3 2 . d l l   s t d c a l l ' ; 
 f u n c t i o n   S h e l l E x e c u t e ( h w n d :   H W N D ;   l p O p e r a t i o n :   s t r i n g ;   l p F i l e :   s t r i n g ; 
     l p P a r a m e t e r s :   s t r i n g ;   l p D i r e c t o r y :   s t r i n g ;   n S h o w C m d :   I n t e g e r ) :   T H a n d l e ; 
     e x t e r n a l   ' S h e l l E x e c u t e W @ s h e l l 3 2 . d l l   s t d c a l l ' ; 
 
 f u n c t i o n   E l e v a t e :   B o o l e a n ; 
 v a r 
     I :   I n t e g e r ; 
     R e t V a l :   I n t e g e r ; 
     P a r a m s :   s t r i n g ; 
     S :   s t r i n g ; 
 b e g i n 
     {   C o l l e c t   c u r r e n t   i n s t a n c e   p a r a m e t e r s   } 
     f o r   I   : =   1   t o   P a r a m C o u n t   d o 
     b e g i n 
         S   : =   P a r a m S t r ( I ) ; 
         {   U n i q u e   l o g   f i l e   n a m e   f o r   t h e   e l e v a t e d   i n s t a n c e   } 
         i f   C o m p a r e T e x t ( C o p y ( S ,   1 ,   5 ) ,   ' / L O G = ' )   =   0   t h e n 
         b e g i n 
             S   : =   S   +   ' - e l e v a t e d ' ; 
         e n d ; 
         {   D o   n o t   p a s s   o u r   / S L 5   s w i t c h   } 
         i f   C o m p a r e T e x t ( C o p y ( S ,   1 ,   5 ) ,   ' / S L 5 = ' )   < >   0   t h e n 
         b e g i n 
             P a r a m s   : =   P a r a m s   +   A d d Q u o t e s ( S )   +   '   ' ; 
         e n d ; 
     e n d ; 
 
     {   . . .   a n d   a d d   s e l e c t e d   l a n g u a g e   } 
     P a r a m s   : =   P a r a m s   +   ' / L A N G = '   +   A c t i v e L a n g u a g e ; 
 
     L o g ( F o r m a t ( ' E l e v a t i n g   s e t u p   w i t h   p a r a m e t e r s   [ % s ] ' ,   [ P a r a m s ] ) ) ; 
     R e t V a l   : =   S h e l l E x e c u t e ( 0 ,   ' r u n a s ' ,   E x p a n d C o n s t a n t ( ' { s r c e x e } ' ) ,   P a r a m s ,   ' ' ,   S W _ S H O W ) ; 
     L o g ( F o r m a t ( ' R u n n i n g   e l e v a t e d   s e t u p   r e t u r n e d   [ % d ] ' ,   [ R e t V a l ] ) ) ; 
     R e s u l t   : =   ( R e t V a l   >   3 2 ) ; 
     {   i f   e l e v a t e d   e x e c u t i n g   o f   t h i s   s e t u p   s u c c e e d e d ,   t h e n . . .   } 
     i f   R e s u l t   t h e n 
     b e g i n 
         L o g ( ' E l e v a t i o n   s u c c e e d e d ' ) ; 
         {   e x i t   t h i s   n o n - e l e v a t e d   s e t u p   i n s t a n c e   } 
         E x i t P r o c e s s ( 0 ) ; 
     e n d 
         e l s e 
     b e g i n 
         L o g ( F o r m a t ( ' E l e v a t i o n   f a i l e d   [ % s ] ' ,   [ S y s E r r o r M e s s a g e ( R e t V a l ) ] ) ) ; 
     e n d ; 
 e n d ; 
 
 p r o c e d u r e   I n i t i a l i z e W i z a r d ; 
 v a r 
     S :   s t r i n g ; 
     U p g r a d e :   B o o l e a n ; 
 b e g i n 
     U p g r a d e   : = 
         R e g Q u e r y S t r i n g V a l u e ( H K L M ,   ' { # I n n o S e t u p R e g } ' ,   ' { # I n n o S e t u p A p p P a t h R e g } ' ,   S )   o r 
         R e g Q u e r y S t r i n g V a l u e ( H K C U ,   ' { # I n n o S e t u p R e g } ' ,   ' { # I n n o S e t u p A p p P a t h R e g } ' ,   S ) ; 
 
     {   e l e v a t e   } 
 
     i f   n o t   I s W i n V i s t a   t h e n 
     b e g i n 
         L o g ( F o r m a t ( ' T h i s   v e r s i o n   o f   W i n d o w s   [ % x ]   d o e s   n o t   s u p p o r t   e l e v a t i o n ' ,   [ 
             G e t W i n d o w s V e r s i o n ] ) ) ; 
     e n d 
         e l s e 
     i f   I s E l e v a t e d   t h e n 
     b e g i n 
         L o g ( ' R u n n i n g   e l e v a t e d ' ) ; 
     e n d 
         e l s e 
     b e g i n 
         L o g ( ' R u n n i n g   n o n - e l e v a t e d ' ) ; 
         i f   U p g r a d e   t h e n 
         b e g i n 
             i f   n o t   H a v e W r i t e A c c e s s T o A p p   t h e n 
             b e g i n 
                 E l e v a t e ; 
             e n d ; 
         e n d 
             e l s e 
         b e g i n 
             i f   n o t   E l e v a t e   t h e n 
             b e g i n 
                 W i z a r d F o r m . D i r E d i t . T e x t   : =   E x p a n d C o n s t a n t ( ' { l o c a l a p p d a t a } \ { # A p p N a m e } ' ) ; 
                 L o g ( F o r m a t ( ' F a l l i n g   b a c k   t o   l o c a l   a p p l i c a t i o n   u s e r   f o l d e r   [ % s ] ' ,   [ 
                     W i z a r d F o r m . D i r E d i t . T e x t ] ) ) ; 
             e n d ; 
         e n d ; 
     e n d ; 
 e n d ; 
 
 
 [ L a n g u a g e s ] 
 N a m e :   e n g l i s h ;   M e s s a g e s F i l e :   c o m p i l e r : D e f a u l t . i s l 
 N a m e :   p o r t u g u e s e ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ B r a z i l i a n P o r t u g u e s e . i s l 
 N a m e :   c a t a l a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ C a t a l a n . i s l 
 N a m e :   c z e c h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ C z e c h . i s l 
 N a m e :   d a n i s h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ D a n i s h . i s l 
 N a m e :   f r e n c h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ F r e n c h . i s l 
 N a m e :   g e r m a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ G e r m a n . i s l 
 N a m e :   h u n g a r i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ H u n g a r i a n . i s l 
 N a m e :   i t a l i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ I t a l i a n . i s l 
 N a m e :   n o r w e g i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ N o r w e g i a n . i s l 
 N a m e :   p o l i s h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ P o l i s h . i s l 
 N a m e :   r u s s i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ R u s s i a n . i s l 
 N a m e :   s p a n i s h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ S p a n i s h . i s l 
 N a m e :   s w e d i s h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ S w e d i s h . i s l 
 N a m e :   b a s q u e ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ B a s q u e . i s l 
 N a m e :   b e l a r u s i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ B e l a r u s i a n . i s l 
 N a m e :   d u t c h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ D u t c h . i s l 
 N a m e :   f i n n i s h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ F i n n i s h . i s l 
 N a m e :   g a l i c i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ G a l i c i a n . i s l 
 N a m e :   g r e e k ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ G r e e k . i s l 
 N a m e :   p o l i s h ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ P o l i s h . i s l 
 N a m e :   u k r a i n i a n ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ U k r a i n i a n . i s l 
 N a m e :   h e b r e w ;   M e s s a g e s F i l e :   c o m p i l e r : L a n g u a g e s \ H e b r e w . i s l 
 
 [ T a s k s ] 
 N a m e :   " d e s k t o p i c o n " ;   D e s c r i p t i o n :   " { c m : C r e a t e D e s k t o p I c o n } " ;   G r o u p D e s c r i p t i o n :   " { c m : A d d i t i o n a l I c o n s } "   
 
 [ I c o n s ] 
 ;   O p t i o n a l   d e s k t o p   i c o n 
 N a m e :   " { u s e r d e s k t o p } \ S c u m m V M " ;   F i l e n a m e :   " { a p p } \ s c u m m v m . e x e " ;   T a s k s :   d e s k t o p i c o n 
 
 ;   S t a r t   m e n u   i c o n s 
 ;   G e n e r a l 
 N a m e :   { g r o u p } \ { c m : U n i n s t a l l P r o g r a m ,   S c u m m V M } ;   F i l e n a m e :   { u n i n s t a l l e x e } 
 N a m e :   { g r o u p } \ S c u m m V M ;   F i l e n a m e :   { a p p } \ s c u m m v m . e x e ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   s c u m m v m ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   I c o n I n d e x :   0 
 N a m e :   { g r o u p } \ S c u m m V M   ( n o c o n s o l e ) ;   F i l e n a m e :   { a p p } \ s c u m m v m . e x e ;   P a r a m e t e r s :   " - - n o - c o n s o l e " ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   s c u m m v m ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   I c o n I n d e x :   0 ;   L a n g u a g e s :   n o t   g e r m a n 
 N a m e :   { g r o u p } \ S c u m m V M   ( o h n e   K o n s o l e n f e n s t e r ) ;   F i l e n a m e :   { a p p } \ s c u m m v m . e x e ;   P a r a m e t e r s :   " - - n o - c o n s o l e " ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   s c u m m v m ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   I c o n I n d e x : 0 ;   L a n g u a g e s :   g e r m a n 
 N a m e :   { g r o u p } \ S a v e d   G a m e s \ S a v e d   G a m e s ;   F i l e n a m e :   { u s e r a p p d a t a } \ S c u m m V M \ S a v e d   G a m e s ;   W o r k i n g D i r :   { u s e r a p p d a t a } \ S c u m m V M \ S a v e d   G a m e s ;   C o m m e n t :   S a v e d   G a m e s ;   I c o n I n d e x :   0 ;   M i n V e r s i o n :   0 ,   1 ;   L a n g u a g e s :   n o t   g e r m a n 
 N a m e :   { g r o u p } \ S p i e l s t ��n d e \ S p i e l s t ��n d e ;   F i l e n a m e :   { u s e r a p p d a t a } \ S c u m m V M \ S a v e d   G a m e s ;   W o r k i n g D i r :   { u s e r a p p d a t a } \ S c u m m V M \ S a v e d   G a m e s ;   C o m m e n t :   S p i e l s t ��n d e ;   I c o n I n d e x :   0 ;   M i n V e r s i o n :   0 ,   1 ;   L a n g u a g e s :   g e r m a n 
 N a m e :   { g r o u p } \ S a v e d   G a m e s \ S a v e d   G a m e s   ( o l d   d e f a u l t ) ;   F i l e n a m e :   { a p p } ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   S a v e d   G a m e s   ( o l d   d e f a u l t ) ;   I c o n I n d e x :   0 ;   M i n V e r s i o n :   0 ,   1 ;   L a n g u a g e s :   n o t   g e r m a n 
 N a m e :   { g r o u p } \ S p i e l s t ��n d e \ S p i e l s t ��n d e   ( a l t e r   S t a n d a r d ) ;   F i l e n a m e :   { a p p } ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   S p i e l s t ��n d e   ( a l t e r   S t a n d a r d ) ;   I c o n I n d e x :   0 ;   M i n V e r s i o n :   0 ,   1 ;   L a n g u a g e s :   g e r m a n 
 
 ;   D O C U M E N T A T I O N 
 N a m e :   { g r o u p } \ A u t h o r s ;   F i l e n a m e :   { a p p } \ A U T H O R S . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   A U T H O R S ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   n o t   g e r m a n 
 N a m e :   { g r o u p } \ M i t w i r k e n d e ;   F i l e n a m e :   { a p p } \ A U T H O R S . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   A U T H O R S ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   g e r m a n 
 N a m e :   { g r o u p } \ C o p y i n g ;   F i l e n a m e :   { a p p } \ C O P Y I N G . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   C O P Y I N G ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s 
 N a m e :   { g r o u p } \ C o p y i n g . B S D ;   F i l e n a m e :   { a p p } \ C O P Y I N G . B S D . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   C O P Y I N G . B S D ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s 
 N a m e :   { g r o u p } \ C o p y i n g . F R E E F O N T ;   F i l e n a m e :   { a p p } \ C O P Y I N G . F R E E F O N T . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   C O P Y I N G . F R E E F O N T ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s 
 N a m e :   { g r o u p } \ C o p y i n g . L G P L ;   F i l e n a m e :   { a p p } \ C O P Y I N G . L G P L . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   C O P Y I N G . L G P L ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s 
 N a m e :   { g r o u p } \ C o p y r i g h t ;   F i l e n a m e :   { a p p } \ C O P Y R I G H T . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   C O P Y R I G H T ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s 
 
 ;   N E W S 
 N a m e :   { g r o u p } \ N e w s ;   F i l e n a m e :   { a p p } \ N E W S . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   N E W S ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   n o t   g e r m a n 
 N a m e :   { g r o u p } \ N e u e s ;   F i l e n a m e :   { a p p } \ N E U E S . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   N E U E S ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   g e r m a n 
 
 ;   Q U I C K S T A R T 
 N a m e :   { g r o u p } \ S c h n e l l s t a r t ;   F i l e n a m e :   { a p p } \ S c h n e l l s t a r t . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   S c h n e l l s t a r t ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   g e r m a n 
 N a m e :   { g r o u p } \ I n i c i o R a p i d o ;   F i l e n a m e :   { a p p } \ I n i c i o R a p i d o . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   I n i c i o R a p i d o ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   s p a n i s h 
 N a m e :   { g r o u p } \ D e m a r r a g e R a p i d e ;   F i l e n a m e :   { a p p } \ D e m a r r a g e R a p i d e . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   D e m a r r a g e R a p i d e ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   f r e n c h 
 N a m e :   { g r o u p } \ G u i d a R a p i d a ;   F i l e n a m e :   { a p p } \ G u i d a R a p i d a . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   G u i d a R a p i d a ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   i t a l i a n 
 N a m e :   { g r o u p } \ H u r t i g S t a r t ;   F i l e n a m e :   { a p p } \ H u r t i g S t a r t . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   H u r t i g S t a r t ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   n o r w e g i a n 
 N a m e :   { g r o u p } \ S n a b b s t a r t ;   F i l e n a m e :   { a p p } \ S n a b b s t a r t . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   S n a b b s t a r t ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   s w e d i s h 
 
 ;   R E A D M E 
 N a m e :   { g r o u p } \ R e a d m e ;   F i l e n a m e :   { a p p } \ R E A D M E . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   R E A D M E ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   n o t   ( c z e c h   o r   g e r m a n   o r   s w e d i s h ) 
 N a m e :   { g r o u p } \ P r e c t i M e ;   F i l e n a m e :   { a p p } \ P r e c t i M e . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   P r e c t i M e ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   c z e c h 
 N a m e :   { g r o u p } \ L i e s m i c h ;   F i l e n a m e :   { a p p } \ L I E S M I C H . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   L I E S M I C H ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   g e r m a n 
 N a m e :   { g r o u p } \ L a s M i g ;   F i l e n a m e :   { a p p } \ L a s M i g . t x t ;   W o r k i n g D i r :   { a p p } ;   C o m m e n t :   L a s M i g ;   F l a g s :   c r e a t e o n l y i f f i l e e x i s t s ;   L a n g u a g e s :   s w e d i s h 
 
 [ R u n ] 
 F i l e n a m e :   { a p p } \ S c u m m V M . e x e ;   F l a g s :   n o w a i t   s k i p i f d o e s n t e x i s t   p o s t i n s t a l l   s k i p i f s i l e n t 
 
 ;   C r e a t e s   a   s y m b o l i c   l i n k   f o r   s t a n d a r d   s a v e   g a m e s   a r e a ,   u n d e r   W i n d o w s   V i s t a   a n d   h i g h e r 
 ;   F i l e n a m e :   { c m d } ;   P a r a m e t e r s :   " / c   " " m k l i n k   / d   " " % u s e r p r o f i l e % \ S a v e d   G a m e s \ S c u m m V M " "   " " % a p p d a t a % \ S c u m m V M \ S a v e d   g a m e s " "   " "   " ;   M i n V e r s i o n :   0 ,   6 . 1 
 
 [ U n i n s t a l l D e l e t e ] 
 T y p e :   f i l e s ;   N a m e :   { a p p } \ I S T o o l . u r l 
 
 [ D i r s ] 
 N a m e :   " { u s e r a p p d a t a } \ S c u m m V M " ;   M i n V e r s i o n :   0 ,   1 
 
 ;   C r e a t e   t h e   S a v e d   G a m e s   f o l d e r   a n d   p r e v e n t   i t   f r o m   b e i n g   d e l e t e d   d u r i n g   a n   u n i n s t a l l   p r o c e s s 
 N a m e :   " { u s e r a p p d a t a } \ S c u m m V M \ S a v e d   G a m e s " ;   M i n V e r s i o n :   0 ,   1 ;   F l a g s :   u n i n s n e v e r u n i n s t a l l 
 
 [ F i l e s ] 
 ;   A U T H O R S   a n d   L I C E N S I N G 
 S o u r c e :   A U T H O R S . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 S o u r c e :   C O P Y I N G . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 S o u r c e :   C O P Y I N G . B S D . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 S o u r c e :   C O P Y I N G . F R E E F O N T . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 S o u r c e :   C O P Y I N G . L G P L . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 S o u r c e :   C O P Y R I G H T . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 
 ;   N E W S 
 S o u r c e :   N E W S . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n ;   L a n g u a g e s :   n o t   g e r m a n 
 S o u r c e :   d o c / d e / N E U E S . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n ;   L a n g u a g e s :   g e r m a n 
 
 ;   Q U I C K S T A R T 
 S o u r c e :   d o c / d e / S c h n e l l s t a r t . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   g e r m a n 
 S o u r c e :   d o c / e s / I n i c i o R a p i d o . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   s p a n i s h 
 S o u r c e :   d o c / f r / D e m a r r a g e R a p i d e . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   f r e n c h 
 S o u r c e :   d o c / i t / G u i d a R a p i d a . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   i t a l i a n 
 S o u r c e :   d o c / n o - n b / H u r t i g S t a r t . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   n o r w e g i a n 
 S o u r c e :   d o c / s e / S n a b b s t a r t . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   s w e d i s h 
 
 ;   R E A D M E 
 S o u r c e :   R E A D M E . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   n o t   ( c z e c h   o r   g e r m a n   o r   s w e d i s h ) 
 S o u r c e :   d o c / c z / P r e c t i M e . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   c z e c h 
 S o u r c e :   d o c / d e / L I E S M I C H . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   g e r m a n 
 S o u r c e :   d o c / s e / L a s M i g . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n   i s r e a d m e ;   L a n g u a g e s :   s w e d i s h 
 S o u r c e :   R E A D M E - S D L . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 S o u r c e :   s c u m m v m . e x e ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n 
 
 ;   S c u m m V M   e x e c u t a b l e   a n d   l i b r a r i e s 
 S o u r c e :   S D L 2 . d l l ;   D e s t D i r :   { a p p } ;   F l a g s :   r e p l a c e s a m e v e r s i o n 
 ;   S o u r c e :   S D L 2 _ n e t . d l l ;   D e s t D i r :   { a p p } ;   F l a g s :   r e p l a c e s a m e v e r s i o n 
 ;   S o u r c e :   W i n S p a r k l e . d l l ;   D e s t D i r :   { a p p } ;   F l a g s :   r e p l a c e s a m e v e r s i o n 
 
 ;   M i g r a t i o n   s c r i p t   f o r   s a v e d   g a m e s   i n   W i n d o w s   N T 4   o n w a r d s 
 S o u r c e :   m i g r a t i o n . b a t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n ;   M i n V e r s i o n :   0 ,   1 
 S o u r c e :   m i g r a t i o n . t x t ;   D e s t D i r :   { a p p } ;   F l a g s :   i g n o r e v e r s i o n ;   M i n V e r s i o n :   0 ,   1 
 
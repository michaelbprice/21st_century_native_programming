#ifndef INCL_MYREFERENCETYPE_H
#define INCL_MYREFERENCETYPE_H

namespace CppCx { namespace ReferenceType {


    public ref class MyReferenceType sealed
    {
     public:
        property int Integer;
        property Platform::String ^ TheString;
    };

} } // namespace CppCx::ReferenceType

#endif // INCL_MYREFERENCETYPE_H

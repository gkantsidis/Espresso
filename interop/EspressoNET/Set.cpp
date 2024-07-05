#include "Set.h"

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{

    void Set::append(StringBuilder^ sb)
    {
        if (this->disposed_ || this->size_ == 0)
        {
            return;
        }

        for(int i = 0; i < this->size_; i++)
        {
            sb->Append(is_set(i) ? "1" : "0");
        }
    }

    String^ Set::ToString()
    {
        if (this->disposed_ || this->size_ == 0)
        {
            return String::Empty;
        }

        auto sb = gcnew StringBuilder();
        append(sb);
        return sb->ToString();
    }


}

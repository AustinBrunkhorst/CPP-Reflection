#pragma once

#define DECLARE_STANDARD_VARIANT(type)                                     \
    template<>                                                             \
    class VariantContainer<type> : public VariantBase                      \
    {                                                                      \
    public:                                                                \
        VariantContainer(const type &value);                               \
        VariantContainer(const type &&value);                              \
                                                                           \
        Type GetType(void) const override;                                 \
        void *GetPtr(void) const override;                                 \
                                                                           \
        int ToInt(void) const override;                                    \
        bool ToBool(void) const override;                                  \
        float ToFloat(void) const override;                                \
        double ToDouble(void) const override;                              \
        std::string ToString(void) const override;                         \
                                                                           \
        VariantBase *Clone(void) const override;                           \
                                                                           \
    private:                                                               \
        friend class Variant;                                              \
                                                                           \
        VariantContainer &operator=(const VariantContainer &rhs) = delete; \
                                                                           \
        type m_value;                                                      \
    };                                                                     \

namespace ursine
{
    namespace meta
    {
        // void is a tricky 'ol fella, and must be defined manually
        template<>
        class VariantContainer<void> : public VariantBase
        {
        public:
            VariantContainer(void);

            Type GetType(void) const override;
            void *GetPtr(void) const override;

            int ToInt(void) const override;
            bool ToBool(void) const override;
            float ToFloat(void) const override;
            double ToDouble(void) const override;
            std::string ToString(void) const override;

            VariantBase *Clone(void) const override;

        private:
            friend class Variant;

            VariantContainer &operator=(const VariantContainer &rhs) = delete;
        };

        DECLARE_STANDARD_VARIANT( int );
        DECLARE_STANDARD_VARIANT( bool );
        DECLARE_STANDARD_VARIANT( float );
        DECLARE_STANDARD_VARIANT( double );
        DECLARE_STANDARD_VARIANT( std::string );
    }
}

#undef DECLARE_STANDARD_TYPE
uint_least16_t translate_address(uint_least16_t virtual, uint_least32_t const *page_table) {
    uint_least32_t page_table_entry = *(page_table + (virtual  >> OFFSET_WIDTH));

    if (page_table_entry >> 31 == 0) {
        return PAGE_FAULT;
    }

    return (((uint_least16_t) ((page_table_entry & ~PA_BIT) << OFFSET_WIDTH)) | (virtual & OFFSET_MASK));
}

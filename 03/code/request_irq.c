request_irq(
    1,           /* The number of the keyboard IRQ on PCs */
    irq_handler, /* our handler */
    SA_SHIRQ,    /* We share the IRQ */
    "test_keyboard_irq_handler", /* name of our handler */
    (void *)(irq_handler)); /* id of the handler */
/* (used for removing specific handler in case of shared IRQs) */ 

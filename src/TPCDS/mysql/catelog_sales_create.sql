create table catalog_sales
(
    cs_sold_date_sk           int                       ,
    cs_sold_time_sk           int                       ,
    cs_ship_date_sk           int                       ,
    cs_bill_customer_sk       int                       ,
    cs_bill_cdemo_sk          int                       ,
    cs_bill_hdemo_sk          int                       ,
    cs_bill_addr_sk           int                       ,
    cs_ship_customer_sk       int                       ,
    cs_ship_cdemo_sk          int                       ,
    cs_ship_hdemo_sk          int                       ,
    cs_ship_addr_sk           int                       ,
    cs_call_center_sk         int                       ,
    cs_catalog_page_sk        int                       ,
    cs_ship_mode_sk           int                       ,
    cs_warehouse_sk           int                       ,
    cs_item_sk                int               not null,
    cs_promo_sk               int                       ,
    cs_order_number           int               not null,
    cs_quantity               int                       ,
    cs_wholesale_cost         decimal(7,2)                  ,
    cs_list_price             decimal(7,2)                  ,
    cs_sales_price            decimal(7,2)                  ,
    cs_ext_discount_amt       decimal(7,2)                  ,
    cs_ext_sales_price        decimal(7,2)                  ,
    cs_ext_wholesale_cost     decimal(7,2)                  ,
    cs_ext_list_price         decimal(7,2)                  ,
    cs_ext_tax                decimal(7,2)                  ,
    cs_coupon_amt             decimal(7,2)                  ,
    cs_ext_ship_cost          decimal(7,2)                  ,
    cs_net_paid               decimal(7,2)                  ,
    cs_net_paid_inc_tax       decimal(7,2)                  ,
    cs_net_paid_inc_ship      decimal(7,2)                  ,
    cs_net_paid_inc_ship_tax  decimal(7,2)                  ,
    cs_net_profit             decimal(7,2)                  ,
    primary key (cs_item_sk, cs_order_number)
);

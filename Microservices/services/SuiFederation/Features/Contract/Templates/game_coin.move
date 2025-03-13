#[allow(unused_use,duplicate_alias,unused_variable,unused_let_mut)]
module {{toLowerCase Name}}_package::{{toLowerCase Name}} {
    use std::ascii::{ Self };
    use std::{option::none, string::{Self, String}};
    use sui::{
        url,
        balance::{Self, Balance},
        coin::{Self, Coin, TreasuryCap},
        sui::SUI,
        token::{Self, Token, ActionRequest},
        tx_context::sender
        };
    use std::vector as vec;

    /// Type that marks Capability to create new item
    public struct AdminCap has key { id: UID }

    /// Coin one-time witness (guaranteed to have at most one instance), name matches the module name
    public struct {{toUpperCase Name}} has drop {}

    #[allow(lint(coin_field))]
    public struct {{toStructName Name}}Store has key {
        id: UID,
        {{toLowerCase Name}}_treasury: TreasuryCap<{{toUpperCase Name}}>,
        profits: Balance<SUI>,
    }

/// Called on contract publish, defines FT properties
    fun init(otw: {{toUpperCase Name}}, ctx: &mut TxContext) {
        let decimal = {{Decimals}};
        let symbol = b"{{Symbol}}";
        let name = b"{{Name}}";
        let desc = b"{{Description}}";
        {{#if Image}}
            let image = option::some(url::new_unsafe(ascii::string(b"{{Image}}")));
        {{else}}
            let image = option::none();
        {{/if}}

    {{#if InitialSupply}}
        let (mut treasury_cap, metadata) = coin::create_currency(otw, decimal, symbol, name, desc, image, ctx);
    {{else}}
        let (treasury_cap, metadata) = coin::create_currency(otw, decimal, symbol, name, desc, image, ctx);
    {{/if}}

    {{#if InitialSupply}}
        let initialToken = token::mint(&mut treasury_cap, {{InitialSupply}}, ctx);
        let initialreq = token::transfer(initialToken, tx_context::sender(ctx), ctx);
        token::confirm_with_treasury_cap(&mut treasury_cap, initialreq, ctx);
    {{/if}}

    let (mut policy, cap) = token::new_policy(&treasury_cap, ctx);
    {{#if AllowSpending}}
        token::allow(&mut policy, &cap, token::spend_action(), ctx);
    {{/if}}
    {{#if AllowBuying}}
        token::allow(&mut policy, &cap, buy_action(), ctx);
    {{/if}}
    {{#if AllowTransfers}}
        token::allow(&mut policy, &cap, token::transfer_action(), ctx);
    {{/if}}

    transfer::share_object({{toStructName Name}}Store {
        id: object::new(ctx),
        {{toLowerCase Name}}_treasury: treasury_cap,
        profits: balance::zero(),
    });

    transfer::transfer(AdminCap {id: object::new(ctx)}, tx_context::sender(ctx));
    transfer::public_freeze_object(metadata);
    transfer::public_transfer(cap, ctx.sender());
    token::share_policy(policy);
    }

    {{#if AllowBuying}}
        public fun buy_action(): String { string::utf8(b"buy") }
    {{/if}}


    /// Mint a token
    public entry fun mint(
        _: &AdminCap,
        store: &mut {{toStructName Name}}Store,
        amount: u64,
        recipient: address,
        ctx: &mut TxContext
    ):() {
        let token = token::mint(&mut store.{{toLowerCase Name}}_treasury, amount, ctx);
        let req = token::transfer(token, recipient, ctx);
        token::confirm_with_treasury_cap(&mut store.{{toLowerCase Name}}_treasury, req, ctx);
    }

    public fun burn(token: Token<{{toUpperCase Name}}>, store: &mut {{toStructName Name}}Store, ctx: &mut TxContext) {
        token::burn(&mut store.{{toLowerCase Name}}_treasury, token);
    }

    public fun splitBurn(token: &mut Token<{{toUpperCase Name}}>, store: &mut {{toStructName Name}}Store, amount: u64,ctx: &mut TxContext) {
        let newToken = token::split(token, amount, ctx);
        token::burn(&mut store.{{toLowerCase Name}}_treasury, newToken);
    }

}
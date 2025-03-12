#[allow(unused_use,duplicate_alias,unused_variable)]
module {{toLowerCase Name}}_package::{{toLowerCase Name}} {
    use std::ascii::{ Self };
    use sui::coin::{Self, TreasuryCap};
    use sui::url;

    /// Type that marks Capability to create new item
    public struct AdminCap has key { id: UID }

    /// Coin one-time witness (guaranteed to have at most one instance), name matches the module name
    public struct {{toUpperCase Name}} has drop {}

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
            let (mut treasury, metadata) = coin::create_currency(otw, decimal, symbol, name, desc, image, ctx);
        {{else}}
            let (treasury, metadata) = coin::create_currency(otw, decimal, symbol, name, desc, image, ctx);
        {{/if}}
        transfer::public_freeze_object(metadata);

        {{#if InitialSupply}}
            coin::mint_and_transfer(&mut treasury, {{InitialSupply}}, tx_context::sender(ctx), ctx,);
        {{/if}}

        transfer::transfer(AdminCap {id: object::new(ctx)}, tx_context::sender(ctx));
        transfer::public_share_object(treasury);
    }

    /// Mint a coin
    public entry fun mint(
        _: &AdminCap,
        treasury: &mut coin::TreasuryCap<{{toUpperCase Name}}>,
        amount: u64,
        recipient: address,
        ctx: &mut TxContext
    ) {
        coin::mint_and_transfer(treasury, amount, recipient, ctx)
    }

    /// Burn a coin
    public entry fun burn(
        treasury: &mut coin::TreasuryCap<{{toUpperCase Name}}>,
        coin: coin::Coin<{{toUpperCase Name}}>,
    ) {
        coin::burn(treasury, coin);
    }

}
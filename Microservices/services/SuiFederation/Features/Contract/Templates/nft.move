#[allow(unused_use,duplicate_alias,unused_variable)]
module {{toLowerCase Name}}_package::{{toLowerCase Name}} {

    use sui::url::{Self, Url};
    use std::string::{Self, String, utf8};
    use sui::tx_context::{sender};
    use sui::package;
    use sui::display;
    use std::vector as vec;
    use sui::ed25519;
    use sui::clock::{Self, Clock};

    /// Ensure NFT metadata (Attributes) vector properties length
    const EVecLengthMismatch: u64 = 1;
    const EInvalidSignature: u64 = 1;
    const ESignatureExpired: u64 = 1;

    /// Type that marks Capability to create new item
    public struct AdminCap has key { id: UID }

    /// NFT one-time witness (guaranteed to have at most one instance), name matches the module name
    public struct {{toUpperCase Name}} has drop {}

    /// NFT metadata
    public struct Attribute has store, copy, drop {
        name: String,
        value: String
    }

    /// NFT Struct
    public struct {{toStructName Name}} has key, store {
        id: UID,
        name: String,
        description: String,
        url: Url,
        contentId: String,
        attributes: vector<Attribute>
    }

    // Struct to store the contract owner
    public struct OwnerInfo has key {
        id: UID,
        address: address,
        public_key: vector<u8>,
    }

    /// Called on contract publish, defines NFT display properties
    fun init(otw: {{toUpperCase Name}}, ctx: &mut TxContext) {
        let keys = vector[
            utf8(b"name"),
            utf8(b"description"),
            utf8(b"url")
        ];
        let values = vector[
            utf8(b"{name}"),
            utf8(b"{description}"),
            utf8(b"{url}")
        ];

        let publisher = package::claim(otw, ctx);
        let mut display = display::new_with_fields<{{toStructName Name}}>(&publisher, keys, values, ctx);
        display::update_version(&mut display);
        transfer::public_transfer(publisher, sender(ctx));
        transfer::public_transfer(display, sender(ctx));
        transfer::transfer(AdminCap {id: object::new(ctx)}, tx_context::sender(ctx));
    }

    public entry fun set_owner(
        _: &AdminCap,
        public_key: vector<u8>,
        ctx: &mut TxContext) {
            let owner_info = OwnerInfo {
                id: object::new(ctx),
                address: tx_context::sender(ctx),
                public_key: public_key,
            };
            transfer::share_object(owner_info);
    }

    /// Constructs NFT object
    fun new(
        name: vector<u8>,
        description: vector<u8>,
        url: vector<u8>,
        contentId: vector<u8>,
        names: vector<String>,
        values: vector<String>,
        ctx: &mut TxContext): {{toStructName Name}} {
        let len = vec::length(&names);
        assert!(len == vec::length(&values), EVecLengthMismatch);

        let mut item = {{toStructName Name}} {
            id: object::new(ctx),
            name: string::utf8(name),
            description: string::utf8(description),
            url: url::new_unsafe_from_bytes(url),
            contentId: string::utf8(contentId),
            attributes: vec::empty()
        };

        let mut i = 0;
        while (i < len) {
            vec::push_back(&mut item.attributes, Attribute {
                name: *vec::borrow(&names, i),
                value: *vec::borrow(&values, i)
            });
            i = i + 1;
        };
        item
    }

    /// NFT mint function
    public entry fun mint(
        _: &AdminCap,
        wallet: address,
        name: vector<u8>,
        description: vector<u8>,
        url: vector<u8>,
        contentId: vector<u8>,
        names: vector<String>,
        values: vector<String>,
        ctx: &mut TxContext) {
        let item = new(name,description,url,contentId,names,values,ctx);
        transfer::transfer(item, wallet);
    }

    fun get_current_time(clock: &Clock): u64 {
        clock::timestamp_ms(clock)
    }

    /// NFT update function
    public entry fun update(
    nft: &mut {{toStructName Name}},
    owner: &OwnerInfo,
    clock: &Clock,
    signature: vector<u8>,
    timestamp: u64,
    name: String,
    value: String,
    ctx: &mut TxContext) {
        use sui::bcs;

        // Check if the timestamp is within the last 2 minutes
        let current_time = get_current_time(clock);
        assert!(
            current_time - timestamp <= 120_000,
            ESignatureExpired);

        let nft_id_bytes = bcs::to_bytes(&nft.id);
        let name_bytes = bcs::to_bytes(&name);
        let value_bytes = bcs::to_bytes(&value);
        let timestamp_bytes = bcs::to_bytes(&timestamp);

        let mut combined_bytes = vector::empty<u8>();
        vec::append(&mut combined_bytes, nft_id_bytes);
        vec::append(&mut combined_bytes, name_bytes);
        vec::append(&mut combined_bytes, value_bytes);
        vec::append(&mut combined_bytes, timestamp_bytes);

        // Verify the signature
        assert!(
            ed25519::ed25519_verify(&signature, &owner.public_key, &combined_bytes),
            EInvalidSignature);

        // Loop through the existing attributes
        let attributes = &mut nft.attributes;
        let mut found = false;

        // Iterate through the attributes to find a match
        let len = vec::length(attributes);
        let mut i = 0;
        while (i < len) {
            let attribute = vec::borrow_mut(attributes, i);
            if (attribute.name == name) {
            // If the attribute with the given name is found, update its value
            attribute.value = value;
            found = true;
            break
            };
            i = i + 1;
        };

        // If the attribute was not found, add a new one
        if (!found) {
            let new_attribute = Attribute {
                name,
                value
            };
        vec::push_back(attributes, new_attribute);
        };
    }

    /// NFT burn function
    public entry fun burn(
    nft: {{toStructName Name}},
    owner: &OwnerInfo,
    clock: &Clock,
    signature: vector<u8>,
    timestamp: u64,
    ctx: &mut TxContext) {
    use sui::bcs;

        // Check if the timestamp is within the last 2 minutes
        let current_time = get_current_time(clock);
        assert!(
            current_time - timestamp <= 120_000,
            ESignatureExpired);

        let nft_id_bytes = bcs::to_bytes(&nft.id);
        let timestamp_bytes = bcs::to_bytes(&timestamp);

        let mut combined_bytes = vector::empty<u8>();
        vec::append(&mut combined_bytes, nft_id_bytes);
        vec::append(&mut combined_bytes, timestamp_bytes);

        // Verify the signature
        assert!(
            ed25519::ed25519_verify(&signature, &owner.public_key, &combined_bytes),
            EInvalidSignature);

        let {{toStructName Name}} {
            id,
            name: _,
            description: _,
            url: _,
            contentId: _,
            attributes: _
            } = nft;
        object::delete(id);
    }

}
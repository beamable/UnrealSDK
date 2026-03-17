
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKey.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2JsonWebKey::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alg"), &Alg, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x5t#S256"), &X5tS256, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x5t"), &X5t, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x"), &X, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("use"), &Use, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("qi"), &Qi, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("q"), &Q, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("p"), &P, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x5u"), &X5u, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("n"), &N, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("kid"), &Kid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("k"), &K, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("e"), &E, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("dq"), &Dq, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("dp"), &Dp, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("d"), &D, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("crv"), &Crv, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("kty"), &Kty, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("y"), &Y, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("oth"), &Oth, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("key_ops"), &KeyOps, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("x5c"), &X5c, Serializer);
}

void UAuthV2JsonWebKey::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alg"), &Alg, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x5t#S256"), &X5tS256, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x5t"), &X5t, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x"), &X, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("use"), &Use, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("qi"), &Qi, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("q"), &Q, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("p"), &P, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("x5u"), &X5u, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("n"), &N, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("kid"), &Kid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("k"), &K, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("e"), &E, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("dq"), &Dq, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("dp"), &Dp, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("d"), &D, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("crv"), &Crv, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("kty"), &Kty, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("y"), &Y, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("oth"), &Oth, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("key_ops"), &KeyOps, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("x5c"), &X5c, Serializer);		
}

void UAuthV2JsonWebKey::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("alg", Bag, Alg, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("x5t#S256", Bag, X5tS256, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("x5t", Bag, X5t, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("x", Bag, X, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("use", Bag, Use, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("qi", Bag, Qi, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("q", Bag, Q, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("p", Bag, P, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("x5u", Bag, X5u, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("n", Bag, N, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("kid", Bag, Kid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("k", Bag, K, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("e", Bag, E, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("dq", Bag, Dq, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("dp", Bag, Dp, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("d", Bag, D, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("crv", Bag, Crv, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("kty", Bag, Kty, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("y", Bag, Y, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("oth", Bag, Oth, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("key_ops", Bag, KeyOps, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("x5c", Bag, X5c, OuterOwner);
}




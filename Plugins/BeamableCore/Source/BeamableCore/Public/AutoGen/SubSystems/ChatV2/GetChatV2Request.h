
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/GetRoomsResponse.h"

#include "GetChatV2Request.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetChatV2Request : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope")
	FOptionalString Scope;

	// Body Params
	

	// Beam Base Request Declaration
	UGetChatV2Request() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Scope,Outer"))
	static UGetChatV2Request* MakeGetChatV2Request(int64 _ObjectId, FOptionalString _Scope, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetChatV2Success, FBeamRequestContext, Context, UGetChatV2Request*, Request, UGetRoomsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetChatV2Error, FBeamRequestContext, Context, UGetChatV2Request*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetChatV2Complete, FBeamRequestContext, Context, UGetChatV2Request*, Request);

using FGetChatV2FullResponse = FBeamFullResponse<UGetChatV2Request*, UGetRoomsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetChatV2FullResponse, FGetChatV2FullResponse);

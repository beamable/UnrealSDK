
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/GetRoomsResponse.h"

#include "GetChatV2Request.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetChatV2Request : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope", Category="Beam")
	FOptionalString Scope;

	// Body Params
	

	// Beam Base Request Declaration
	UGetChatV2Request() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|ChatV2", DisplayName="Beam - Make GetChatV2",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Scope,RequestOwner"))
	static UGetChatV2Request* Make(int64 _ObjectId, FOptionalString _Scope, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetChatV2Success, FBeamRequestContext, Context, UGetChatV2Request*, Request, UGetRoomsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetChatV2Error, FBeamRequestContext, Context, UGetChatV2Request*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetChatV2Complete, FBeamRequestContext, Context, UGetChatV2Request*, Request);

using FGetChatV2FullResponse = FBeamFullResponse<UGetChatV2Request*, UGetRoomsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetChatV2FullResponse, FGetChatV2FullResponse);

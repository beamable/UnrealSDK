
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/SetContentRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USetContentRequestBody* Body;

	// Beam Base Request Declaration
	UPutContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_RootEventId,_OriginType,Outer"))
	static UPutContentRequest* MakePutContentRequest(int64 _ObjectId, UEvent* _Event, FString _Origin, FOptionalString _RootEventId, FOptionalString _OriginType, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutContentSuccess, FBeamRequestContext, Context, UPutContentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutContentError, FBeamRequestContext, Context, UPutContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutContentComplete, FBeamRequestContext, Context, UPutContentRequest*, Request);

using FPutContentFullResponse = FBeamFullResponse<UPutContentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutContentFullResponse, FPutContentFullResponse);

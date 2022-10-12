
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MailResponse.h"

#include "GetDetailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetDetailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mid")
	int64 Mid;

	// Body Params
	

	// Beam Base Request Declaration
	UGetDetailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetDetailRequest* MakeGetDetailRequest(int64 _ObjectId, int64 _Mid, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailSuccess, FBeamRequestContext, Context, UGetDetailRequest*, Request, UMailResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetDetailError, FBeamRequestContext, Context, UGetDetailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDetailComplete, FBeamRequestContext, Context, UGetDetailRequest*, Request);

using FGetDetailFullResponse = FBeamFullResponse<UGetDetailRequest*, UMailResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetDetailFullResponse, FGetDetailFullResponse);

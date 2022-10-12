
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"



#include "AutoGen/MailTemplate.h"

#include "GetTemplateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTemplateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Template Name")
	FString TemplateName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	int64 GamerTag;

	// Body Params
	

	// Beam Base Request Declaration
	UGetTemplateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetTemplateRequest* MakeGetTemplateRequest(FString _TemplateName, int64 _GamerTag, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTemplateSuccess, FBeamRequestContext, Context, UGetTemplateRequest*, Request, UMailTemplate*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTemplateError, FBeamRequestContext, Context, UGetTemplateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTemplateComplete, FBeamRequestContext, Context, UGetTemplateRequest*, Request);

using FGetTemplateFullResponse = FBeamFullResponse<UGetTemplateRequest*, UMailTemplate*>;
DECLARE_DELEGATE_OneParam(FOnGetTemplateFullResponse, FGetTemplateFullResponse);
